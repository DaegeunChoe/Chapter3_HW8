#include "Fragments/ItemFragment_InstantParticle.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

void UItemFragment_InstantParticle::OnBeginPlay()
{
	if (PickupParticle && ItemActor)
	{
		Particle = UGameplayStatics::SpawnEmitterAtLocation(
			ItemActor->GetWorld(),
			PickupParticle,
			ItemActor->GetActorLocation(),
			ItemActor->GetActorRotation(),
			true);

		if (Particle)
		{
			GetWorld()->GetTimerManager().SetTimer(
				DestroyParticleTimerHandle, this, &ThisClass::RemoveParticle, 2.0f, false
			);
		}
	}
}

void UItemFragment_InstantParticle::OnEndPlay()
{
	/*if (DestroyParticleTimerHandle.IsValid())
	{
		if (IsValid(ItemActor))
		{
			ItemActor->GetWorldTimerManager().ClearTimer(DestroyParticleTimerHandle);
		}
		RemoveParticle();
	}*/
}

void UItemFragment_InstantParticle::RemoveParticle()
{
	if (Particle)
	{
		Particle->DestroyComponent();
		Particle = nullptr;
	}
}
