#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ItemFragment_PickupAndRemove.generated.h"

UCLASS()
class UItemFragment_PickupAndRemove : public UItemFragment
{
	GENERATED_BODY()

public:
	virtual void OnEndPlay() override;
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp) override;

	void RemoveItemActor();

	FTimerHandle RemoveTimerHandle;
};
