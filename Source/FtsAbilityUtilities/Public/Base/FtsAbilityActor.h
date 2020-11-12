// (c) 2020 by FreetimeStudio

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FtsAbilityActor.generated.h"


/**
 * \brief Base class for actors using the Gameplay Ability System
 */
UCLASS()
class FTSABILITYUTILITIES_API AFtsAbilityActor : public AActor
	, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystem;

public:	
	AFtsAbilityActor();

	//IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	};

protected:
	virtual void BeginPlay() override;
};
