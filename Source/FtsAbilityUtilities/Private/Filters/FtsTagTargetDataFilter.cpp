#include "FtsTagTargetDataFilter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilities/Public/AbilitySystemGlobals.h"

bool FFtsTagTargetDataFilter::FilterPassesForActor(const AActor* ActorToBeFiltered) const
{
    if(!Super::FilterPassesForActor(ActorToBeFiltered))
    {
        return false;
    }

    auto bHasTag = false;

    const UAbilitySystemComponent* AbilitySystem = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(ActorToBeFiltered);
    if(IsValid(AbilitySystem))
    {
        bHasTag = AbilitySystem->HasMatchingGameplayTag(Tag);
    }

    return (bReverseFilter ^ bHasTag);
}
