#include "Fragments/ItemFragment_PickupParticle.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

void UItemFragment_PickupParticle::OnEndPlay()
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

void UItemFragment_PickupParticle::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp)
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

void UItemFragment_PickupParticle::RemoveParticle()
{
	if (Particle)
	{
		Particle->DestroyComponent();
		Particle = nullptr;
	}
}
