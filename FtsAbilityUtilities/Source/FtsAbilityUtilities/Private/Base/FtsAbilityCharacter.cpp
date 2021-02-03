// (c) 2020 by FreetimeStudio


#include "Base/FtsAbilityCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemComponent.h"

AFtsAbilityCharacter::AFtsAbilityCharacter()
{
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetIsReplicated(true);

	// Mixed mode means we only are replicated the GEs to ourself, not the GEs to simulated proxies. If another character receives a GE,
	// we won't be told about it by the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
    AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void AFtsAbilityCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	auto ASC = GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	ASC->InitAbilityActorInfo(this, this);
}
