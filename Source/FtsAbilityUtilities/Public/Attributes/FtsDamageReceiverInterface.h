// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "UObject/Interface.h"
#include "GameplayTags/Classes/GameplayTagContainer.h"
#include "FtsDamageReceiverInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFtsDamageReceiverInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface to implement damage handling like in vanilla unreal for GAS
 */
class FTSABILITYUTILITIES_API IFtsDamageReceiverInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category="Damage")
	void OnAbilityDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, APawn* InstigatorPawn, AActor* DamageCauser);
};
