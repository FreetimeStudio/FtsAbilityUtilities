// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FtsAbilitiesFunctionLibrary.generated.h"

class UGameplayEffect;

USTRUCT()
struct FTSABILITYUTILITIES_API FFtsAbilityInfo
{
	GENERATED_BODY();

	UPROPERTY()
    TWeakObjectPtr<UAbilitySystemComponent> ASC;
	
	UPROPERTY()
    TWeakObjectPtr<AActor> Actor;

	UPROPERTY()
	TWeakObjectPtr<AController> Controller;

	UPROPERTY()
	TWeakObjectPtr<APawn> Pawn;

	FFtsAbilityInfo();
};

USTRUCT(BlueprintType)
struct FTSABILITYUTILITIES_API FFtsModifierInfo
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadWrite, Category="Modifier")
    FGameplayAttribute Attribute;
	
	UPROPERTY(BlueprintReadWrite, Category="Modifier")
    float Magnitude;
};

/**
 * 
 */
UCLASS()
class FTSABILITYUTILITIES_API UFtsAbilitiesFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Abilities")
    static bool HasAnyActivatableAbility(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTagContainer& GameplayTagContainer);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
    static int32 GetTagCount(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag GameplayTag);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Abilities")
	static UAbilitySystemComponent* GetSourceAbilitySystemComponentFromHandle(FActiveGameplayEffectHandle Handle);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Abilities")
	static bool WasGameplayEffectAppliedSuccessfully(FActiveGameplayEffectHandle Handle);

	static void GetAbilitySourceInfoFromCallback(const FGameplayEffectModCallbackData& Data, FFtsAbilityInfo& OutInfo);
	static void GetAbilityTargetInfoFromCallback(const FGameplayEffectModCallbackData& Data, FFtsAbilityInfo& OutInfo);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Abilities")
	static void GetGameplayEffectModifiers(TSubclassOf<UGameplayEffect> EffectClass, TArray<FFtsModifierInfo>& OutModifiers);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Abilities")
	static float GetGameplayEffectPeriod(TSubclassOf<UGameplayEffect> EffectClass);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Abilities")
    static bool GetModifierMagnitude(TSubclassOf<UGameplayEffect> EffectClass, FGameplayAttribute Attribute, float& OutMagnitude);
};
