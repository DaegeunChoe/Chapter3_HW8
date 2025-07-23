#include "SpawnVolume.h"
#include "BaseItem.h"
#include "ItemSpawnRow.h"
#include "Components/BoxComponent.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneComp);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(SceneComp);

	ItemDataTable = nullptr;
}

ABaseItem* ASpawnVolume::SpawnRandomItem()
{
	FItemSpawnRow* SelectedRow = GetRandomItem();
	if (SelectedRow == nullptr)
	{
		return nullptr;
	}

	UClass* ItemClass = SelectedRow->ItemClass.Get();
	if (ItemClass == nullptr)
	{
		return nullptr;
	}
	return SpawnItem(ItemClass);
}

ABaseItem* ASpawnVolume::SpawnSpikeItem()
{
	if (SpikeItemClass != nullptr)
	{
		return GetWorld()->SpawnActor<ABaseItem>(SpikeItemClass, GetRandomXYPointInVolume(-300.0f), FRotator::ZeroRotator);
	}
	else
	{
		return nullptr;
	}
}

ABaseItem* ASpawnVolume::SpawnExplosion()
{
	if (ExplosionClass != nullptr)
	{
		return GetWorld()->SpawnActor<ABaseItem>(ExplosionClass, GetRandomPointInVolume(), FRotator::ZeroRotator);
	}
	else
	{
		return nullptr;
	}
}

ABaseItem* ASpawnVolume::SpawnItem(TSubclassOf<ABaseItem> ItemClass)
{
	if (ItemClass == nullptr)
	{
		return nullptr;
	}

	return GetWorld()->SpawnActor<ABaseItem>(ItemClass, GetRandomPointInVolume(), FRotator::ZeroRotator);
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent(); // 중심부터 끝 까지의 거리
	FVector BoxOrigin = SpawningBox->GetComponentLocation(); // 중심 위치

	FVector Random(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);

	return BoxOrigin + Random;
}

FVector ASpawnVolume::GetRandomXYPointInVolume(float Z) const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent(); // 중심부터 끝 까지의 거리
	FVector BoxOrigin = SpawningBox->GetComponentLocation(); // 중심 위치

	FVector Random(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		Z
	);

	return BoxOrigin + Random;
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	if (ItemDataTable == nullptr)
	{
		return nullptr;
	}
	
	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));
	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty())
	{
		return nullptr;
	}

	float TotalChance = 0.0f;
	for (FItemSpawnRow* Row : AllRows)
	{
		if (Row != nullptr)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulateChance = 0.0f;

	for (FItemSpawnRow* Row : AllRows)
	{
		if (Row != nullptr)
		{
			AccumulateChance += Row->SpawnChance;
			if (AccumulateChance >= RandValue)
			{
				return Row;
			}
		}
	}
	return nullptr;
}
