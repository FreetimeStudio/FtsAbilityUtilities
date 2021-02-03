// (c) 2020 by FreetimeStudio


#include "TargetActors/FtsBlueprintableTargetActor.h"

#include "Abilities/GameplayAbility.h"

AFtsBlueprintableTargetActor::AFtsBlueprintableTargetActor()
    : Super()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickGroup = TG_PostUpdateWork;
}

void AFtsBlueprintableTargetActor::StartTargeting(UGameplayAbility* Ability)
{
    Super::StartTargeting(Ability);
    
    SourceActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
    AttachToActor(SourceActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

    if (ReticleClass)
    {
        AGameplayAbilityWorldReticle* SpawnedReticleActor = GetWorld()->SpawnActor<AGameplayAbilityWorldReticle>(ReticleClass, GetActorLocation(), GetActorRotation());
        if (SpawnedReticleActor)
        {
            SpawnedReticleActor->InitializeReticle(this, MasterPC, ReticleParams);
            ReticleActor = SpawnedReticleActor;

            // This is to catch cases of playing on a listen server where we are using a replicated reticle actor.
            // (In a client controlled player, this would only run on the client and therefor never replicate. If it runs
            // on a listen server, the reticle actor may replicate. We want consistancy between client/listen server players.
            // Just saying 'make the reticle actor non replicated' isnt a good answer, since we want to mix and match reticle
            // actors and there may be other targeting types that want to replicate the same reticle actor class).
            if (!ShouldProduceTargetDataOnServer)
            {
                SpawnedReticleActor->SetReplicates(false);
            }
        }
    }
}

void AFtsBlueprintableTargetActor::ConfirmTargetingAndContinue()
{
    check(ShouldProduceTargetData());
    FGameplayAbilityTargetDataHandle Handle = MakeTargetData();
    TargetDataReadyDelegate.Broadcast(Handle);
}

FGameplayAbilityTargetDataHandle AFtsBlueprintableTargetActor::MakeTargetData_Implementation() const
{
    const TArray<TWeakObjectPtr<AActor>> TargetDataActors;
    return StartLocation.MakeTargetDataHandleFromActors(TargetDataActors);
}

void AFtsBlueprintableTargetActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (ReticleActor.IsValid())
    {
        ReticleActor.Get()->Destroy();
    }

    Super::EndPlay(EndPlayReason);
}
