#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;
class ABaseItem;
struct FItemSpawnRow;

UCLASS()
class SPARTAPROJECT_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:
	ASpawnVolume();

	UFUNCTION(BlueprintCallable)
	ABaseItem* SpawnRandomItem();

	UFUNCTION(BlueprintCallable)
	ABaseItem* SpawnSpikeItem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TObjectPtr<UDataTable> ItemDataTable;

protected:
	FVector GetRandomPointInVolume() const;
	FVector GetRandomXYPointInVolume(float Z) const;
	FItemSpawnRow* GetRandomItem() const;
	ABaseItem* SpawnItem(TSubclassOf<ABaseItem> ItemClass);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	TObjectPtr<USceneComponent> SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	TObjectPtr<UBoxComponent> SpawningBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<ABaseItem> SpikeItemClass;
};
