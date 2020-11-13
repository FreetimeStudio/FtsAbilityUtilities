// (c) 2020 by FreetimeStudio


#include "FtsAutoActivatingGameplayAbility.h"
#include "AbilitySystemComponent.h"

UFtsAutoActivatingGameplayAbility::UFtsAutoActivatingGameplayAbility()
: Super()
{
	bActivateAbilityOnGranted = false;	
}
void UFtsAutoActivatingGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateAbilityOnGranted)
	{
		//Don't activate if not all required tags are present
		if(!ActorInfo->AbilitySystemComponent->HasAllMatchingGameplayTags(GrantActivationRequiredTags))
		{
			return;
		}

		//Don't activate if any ignore tag is present
		if(ActorInfo->AbilitySystemComponent->HasAnyMatchingGameplayTags(GrantActivationIgnoredTags))
		{
			return;
		}
		
		bool ActivatedAbility = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
