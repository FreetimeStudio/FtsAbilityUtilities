// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "FtsAutoActivatingGameplayAbility.generated.h"

/**
 * Code with help from https://github.com/tranek/GASShooter 
 */
UCLASS()
class FTSABILITYUTILITIES_API UFtsAutoActivatingGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFtsAutoActivatingGameplayAbility();
	
	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilities forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool bActivateAbilityOnGranted;	

	// Ability will only auto activate when all these tags are present
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability", meta=(EditCondition="bActivateAbilityOnGranted"))
	FGameplayTagContainer GrantActivationRequiredTags;	

	// Ability will only auto activate when none of these tags are present
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability", meta=(EditCondition="bActivateAbilityOnGranted"))
	FGameplayTagContainer GrantActivationIgnoredTags;	

	// If an ability is marked as 'ActivateAbilityOnGranted', activate them immediately when given here
	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
