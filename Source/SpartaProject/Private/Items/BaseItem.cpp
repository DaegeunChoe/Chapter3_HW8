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
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemBeginOverlap);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnItemEndOverlap);

	for (UItemFragment* Fragment : Fragments)
	{
		if (Fragment)
		{
			Fragment->SetItemActor(this);
			Fragment->OnBeginPlay();
		}
	}
}

void ABaseItem::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Collision->OnComponentBeginOverlap.Clear();
	Collision->OnComponentEndOverlap.Clear();

	for (UItemFragment* Fragment : Fragments)
	{
		if (Fragment)
		{
			Fragment->OnEndPlay();
		}
	}

	Super::EndPlay(EndPlayReason);
}

void ABaseItem::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (UItemFragment* Fragment : Fragments)
	{
		if (Fragment && IsValid(OtherActor) && OtherActor->ActorHasTag(TEXT("Player")))
		{
			Fragment->OnBeginOverlap(OverlappedComp, OtherActor, OtherComp);
		}
	}
}

void ABaseItem::OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
