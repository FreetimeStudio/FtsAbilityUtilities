// (c) 2020 by FreetimeStudio


#include "FtsAbilitiesFunctionLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Gameframework/PlayerController.h"

FFtsAbilityInfo::FFtsAbilityInfo()
{
    ASC = nullptr;
    Actor = nullptr;
    Controller = nullptr;
    Pawn = nullptr;
}


bool UFtsAbilitiesFunctionLibrary::HasAnyActivatableAbility(UAbilitySystemComponent* AbilitySystemComponent,
    const FGameplayTagContainer& GameplayTagContainer)
{
    if (ensure(IsValid(AbilitySystemComponent)))
    {
        TArray<FGameplayAbilitySpec*> MatchingGameplayAbilities;
        AbilitySystemComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, MatchingGameplayAbilities);

        return MatchingGameplayAbilities.Num() > 0;
    }

    return false;
}

int32 UFtsAbilitiesFunctionLibrary::GetTagCount(UAbilitySystemComponent* AbilitySystemComponent,
    const FGameplayTag GameplayTag)
{
    if(!AbilitySystemComponent)
    {
        return 0;
    }
	
    return AbilitySystemComponent->GetTagCount(GameplayTag);
}

UAbilitySystemComponent* UFtsAbilitiesFunctionLibrary::GetSourceAbilitySystemComponentFromHandle(
    FActiveGameplayEffectHandle Handle)
{
    return Handle.GetOwningAbilitySystemComponent();
}

bool UFtsAbilitiesFunctionLibrary::WasGameplayEffectAppliedSuccessfully(FActiveGameplayEffectHandle Handle)
{
    return Handle.WasSuccessfullyApplied();
}

void UFtsAbilitiesFunctionLibrary::GetAbilitySourceInfoFromCallback(const FGameplayEffectModCallbackData& Data,
                                                                    FFtsAbilityInfo& OutInfo)
{
    const auto Context = Data.EffectSpec.GetContext();
    UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
    OutInfo.ASC = Source;

    // Get the Source actor
    if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
    {
        OutInfo.Actor = Source->AbilityActorInfo->AvatarActor;
        OutInfo.Controller = Source->AbilityActorInfo->PlayerController;

        //If Source controller is not set, try getting it from the actor
        if (OutInfo.Controller == nullptr && OutInfo.Actor != nullptr)
        {
            OutInfo.Pawn = Cast<APawn>(OutInfo.Actor);
            if (OutInfo.Pawn.IsValid())
            {
                OutInfo.Controller = OutInfo.Pawn->GetController();
            }
        }
	
        // Use the controller to find the source pawn
        if (OutInfo.Controller.IsValid())
        {
            OutInfo.Pawn = OutInfo.Controller->GetPawn();
        }
	
        // Set the causer actor based on context if it's set
        if (Context.GetEffectCauser())
        {
            OutInfo.Actor = Context.GetEffectCauser();
        }
    }
}

void UFtsAbilitiesFunctionLibrary::GetAbilityTargetInfoFromCallback(const FGameplayEffectModCallbackData& Data,
    FFtsAbilityInfo& OutInfo)
{
    if (Data.Target.AbilityActorInfo.IsValid())
    {
        OutInfo.ASC = Data.Target.AbilityActorInfo->AbilitySystemComponent.Get();
        OutInfo.Actor = Data.Target.AbilityActorInfo->AvatarActor.Get();
        OutInfo.Controller = Data.Target.AbilityActorInfo->PlayerController.Get();
        OutInfo.Pawn = Cast<APawn>(OutInfo.Actor.Get());
    }
}

void UFtsAbilitiesFunctionLibrary::GetGameplayEffectModifiers(TSubclassOf<UGameplayEffect> EffectClass, TArray<FFtsModifierInfo>& OutModifiers)
{
    const auto GE = Cast<UGameplayEffect>(EffectClass.GetDefaultObject());
    if(!GE)
    {
        return;
    }

    for(auto Modifier : GE->Modifiers)
    {
        FFtsModifierInfo Info;
        Info.Attribute =  Modifier.Attribute;
        Info.Magnitude = Modifier.Magnitude.Value;
        OutModifiers.Add(Info);
    }
}

float UFtsAbilitiesFunctionLibrary::GetGameplayEffectPeriod(TSubclassOf<UGameplayEffect> EffectClass)
{
    const auto GE = Cast<UGameplayEffect>(EffectClass.GetDefaultObject());
    if(!GE)
    {
        return 0;
    }

    return GE->Period.Value;
}

bool UFtsAbilitiesFunctionLibrary::GetModifierMagnitude(TSubclassOf<UGameplayEffect> EffectClass,
    FGameplayAttribute Attribute, float& OutMagnitude)
{
    const auto GE = Cast<UGameplayEffect>(EffectClass.GetDefaultObject());
    if(!GE)
    {
        return false;
    }

    for(auto Modifier : GE->Modifiers)
    {
        if(Modifier.Attribute == Attribute)
        {
            OutMagnitude = Modifier.Magnitude.Value;
            return true;
        }
    }

    return false;
}

FGameplayTargetDataFilterHandle UFtsAbilitiesFunctionLibrary::MakeTagFilterHandle(FFtsTagTargetDataFilter Filter,
                                                                                  AActor* FilterActor)
{
    FGameplayTargetDataFilter* NewFilter = new FFtsTagTargetDataFilter(Filter);
    NewFilter->InitializeFilterContext(FilterActor);

    FGameplayTargetDataFilterHandle FilterHandle;
    FilterHandle.Filter = TSharedPtr<FGameplayTargetDataFilter>(NewFilter);
    return FilterHandle;
}
