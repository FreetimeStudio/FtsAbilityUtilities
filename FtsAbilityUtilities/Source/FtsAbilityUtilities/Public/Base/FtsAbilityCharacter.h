// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "FtsAbilityCharacter.generated.h"

class UGameplayEffect;

UCLASS()
class FTSABILITYUTILITIES_API AFtsAbilityCharacter : public ACharacter
	, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystem;

public:
	// Sets default values for this character's properties
	AFtsAbilityCharacter();

	//IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	};
	
	virtual void PossessedBy(AController* NewController) override;
};
