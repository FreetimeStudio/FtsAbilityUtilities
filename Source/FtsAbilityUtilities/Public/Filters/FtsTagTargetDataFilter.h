#pragma once

#include "GameplayTagContainer.h"
#include "Abilities/GameplayAbilityTargetDataFilter.h"
#include "TagTargetDataFilter.generated.h"

USTRUCT(BlueprintType)
struct FTSABILITYUTILITIES_API FTagTargetDataFilter : public FGameplayTargetDataFilter
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Filter")
    FGameplayTag Tag;

    /** Returns true if the actor passes the filter and will be targeted */
    virtual bool FilterPassesForActor(const AActor* ActorToBeFiltered) const override;
};