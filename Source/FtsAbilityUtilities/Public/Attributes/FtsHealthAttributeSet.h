// (c) 2020 by FreetimeStudio

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeMacros.h"

#include "FtsHealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class FTSABILITYUTILITIES_API UFtsHealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:
	/** Current Health, when 0 we expect owner to die. Capped by MaxHealth */
    UPROPERTY(EditAnywhere, Category = "Attributes", SaveGame)
    FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UFtsHealthAttributeSet, Health)

    /** MaxHealth is its own attribute, since GameplayEffects may modify it */
    UPROPERTY(EditAnywhere, Category = "Attributes", SaveGame)
    FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UFtsHealthAttributeSet, MaxHealth)

	/** Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage, which then turns into -Health */
    UPROPERTY(EditAnywhere, Category = "Attributes", SaveGame)
    FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UFtsHealthAttributeSet, Damage)

    /** Defense is subtracted from incoming damage */
    UPROPERTY(EditAnywhere, Category = "Attributes", SaveGame)
    FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UFtsHealthAttributeSet, Defense)

public:
	UFtsHealthAttributeSet();
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
	void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
};
