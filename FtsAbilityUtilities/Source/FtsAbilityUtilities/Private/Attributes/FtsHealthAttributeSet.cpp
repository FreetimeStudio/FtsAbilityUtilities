// (c) 2020 by FreetimeStudio


#include "Attributes/FtsHealthAttributeSet.h"
#include "Attributes/FtsDamageReceiverInterface.h"
#include "FtsAbilitiesFunctionLibrary.h"
#include "GameplayEffectExtension.h"

UFtsHealthAttributeSet::UFtsHealthAttributeSet()
: Super()
{
    Health = 100.f;
    MaxHealth = 100.f;
    Defense = 0.f;
}

void UFtsHealthAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

    FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
    UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
    const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

    FFtsAbilityInfo SourceInfo;
    UFtsAbilitiesFunctionLibrary::GetAbilitySourceInfoFromCallback(Data, SourceInfo);

    FFtsAbilityInfo TargetInfo;
    UFtsAbilitiesFunctionLibrary::GetAbilityTargetInfoFromCallback(Data, TargetInfo);

    FGameplayTagContainer AssetTags;
    Data.EffectSpec.GetAllAssetTags(AssetTags);

    //Handle Damage dealing by subtracting damage from health
    if (Data.EvaluatedData.Attribute == GetDamageAttribute())
    {
        // Try to extract a hit result
        FHitResult HitResult;
        if (Context.GetHitResult())
        {
            HitResult = *Context.GetHitResult();
        }
	
        // Store a local copy of the amount of damage done and clear the damage attribute
        float RemainingDamage = GetDamage();
        SetDamage(0.f);

        RemainingDamage = RemainingDamage - GetDefense();
		
        if (RemainingDamage > 0.f)
        {
            // Apply the health change and then clamp it
            const float NewHealth = GetHealth() - RemainingDamage;
            SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));
	
            if (TargetInfo.Actor.IsValid() && TargetInfo.Actor->Implements<UFtsDamageReceiverInterface>())
            {
                IFtsDamageReceiverInterface::Execute_OnAbilityDamage(TargetInfo.Actor.Get(), RemainingDamage, HitResult, AssetTags, SourceInfo.Pawn.Get(), SourceInfo.Actor.Get());
            }
        }
    }    
}

void UFtsHealthAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
    if (GetHealthAttribute() == Attribute)
    {
        NewValue = FMath::Clamp<float>(NewValue, 0.f, GetMaxHealth());
        return;
    }
}

