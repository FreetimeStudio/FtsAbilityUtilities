// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "FtsBlueprintableTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class FTSABILITYUTILITIES_API AFtsBlueprintableTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

protected:
	TWeakObjectPtr<AGameplayAbilityWorldReticle> ReticleActor;

public:
	AFtsBlueprintableTargetActor();
	
	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override;

	UFUNCTION(BlueprintNativeEvent, Category="Ability")
	FGameplayAbilityTargetDataHandle MakeTargetData() const;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
};
