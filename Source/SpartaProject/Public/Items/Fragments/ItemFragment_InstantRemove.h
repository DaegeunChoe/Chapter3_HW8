#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ItemFragment_InstantRemove.generated.h"

UCLASS()
class UItemFragment_InstantRemove : public UItemFragment
{
	GENERATED_BODY()

public:
	virtual void OnBeginPlay() override;
	virtual void OnEndPlay() override;

	void RemoveItemActor();

	FTimerHandle RemoveTimerHandle;
};
