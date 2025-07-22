#pragma once

#include "CoreMinimal.h"
#include "Fragments/ItemFragment_DelayedAction.h"
#include "ItemFragment_DelayedSpawnActor.generated.h"

UCLASS()
class UItemFragment_DelayedSpawnActor : public UItemFragment_DelayedAction
{
	GENERATED_BODY()

public:
	virtual void DelayedAction() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ActorClassToSpawn;
};
