#include "BaseItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneComp);

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	Collision->SetupAttachment(SceneComp);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemBeginOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);
}

void ABaseItem::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	if (DestroyParticleTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(DestroyParticleTimerHandle);
	}
	DestroyItem();
}

void ABaseItem::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherActor) && OtherActor->ActorHasTag(TEXT("Player")))
	{
		ActivateItem(OtherActor);
	}
}

void ABaseItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABaseItem::ActivateItem(AActor* Activator)
{
	if (PickupParticle)
	{
		Particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PickupParticle, GetActorLocation(), GetActorRotation(), true);
	}
	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
	}

	if (Particle)
	{
		GetWorld()->GetTimerManager().SetTimer(
			DestroyParticleTimerHandle,
			this, &ABaseItem::RemoveParticle, 2.0f, false
		);
	}
}

FName ABaseItem::GetItemType() const
{
	return ItemType;
}

void ABaseItem::DestroyItem()
{
	Destroy();
}

void ABaseItem::RemoveParticle()
{
	if (Particle)
	{
		Particle->DestroyComponent();
	}
}
