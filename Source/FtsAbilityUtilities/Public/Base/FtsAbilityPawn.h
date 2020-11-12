// (c) 2020 by FreetimeStudio

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FtsAbilityPawn.generated.h"

UCLASS()
class FTSABILITYUTILITIES_API AFtsAbilityPawn : public APawn
	, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities, meta = (AllowPrivateAccess = "true"))
    UAbilitySystemComponent* AbilitySystem;

public:
	// Sets default values for this pawn's properties
	AFtsAbilityPawn();
	void PossessedBy(AController* NewController) override;

	//IAbilitySystemInterface
	UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystem;
	};
};
