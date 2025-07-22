#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

AMineItem::AMineItem()
{
	ExplosionDelay = 5.0f;
	ExplosionRadius = 300.0f;
	ExplosionDamage = 30;
	ItemType = TEXT("Mine");
	bHasExploded = false;

	ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
	ExplosionCollision->InitSphereRadius(ExplosionRadius);
	ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ExplosionCollision->SetupAttachment(SceneComp);
}

void AMineItem::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	if (DestroyExplodedParticleTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(DestroyExplodedParticleTimerHandle);
	}
	RemoveExplodedParticle();
	Super::EndPlay(EndPlayReason);
}

void AMineItem::ActivateItem(AActor* Activator)
{
	if (bHasExploded)
	{
		return;
	}
	bHasExploded = true;

	Super::ActivateItem(Activator);
	GetWorld()->GetTimerManager().SetTimer(
		ExplosionTimerHandle, this, &AMineItem::Explode, ExplosionDelay, false);
}

void AMineItem::DestroyItem()
{
	if (ExplosionTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ExplosionTimerHandle);
	}
	Super::DestroyItem();
}

void AMineItem::Explode()
{
	if (ExplosionParticle)
	{
		ExplodedParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation(), GetActorRotation(), false);
	}
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	}

	TArray<AActor*> OverlappingActors;
	ExplosionCollision->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		if (IsValid(Actor) && Actor->ActorHasTag(TEXT("Player")))
		{
			UGameplayStatics::ApplyDamage(Actor, ExplosionDamage, nullptr, this, UDamageType::StaticClass());
		}
	}
	DestroyItem();

	if (ExplodedParticle)
	{
		GetWorld()->GetTimerManager().SetTimer(
			DestroyExplodedParticleTimerHandle,
			this, &AMineItem::RemoveExplodedParticle, 2.0f, false
		);
	}
}

void AMineItem::RemoveExplodedParticle()
{
	if (ExplodedParticle)
	{
		ExplodedParticle->DestroyComponent();
	}
}

