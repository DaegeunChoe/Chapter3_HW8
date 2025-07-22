#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ItemFragment_DelayedAction.generated.h"

UCLASS()
class UItemFragment_DelayedAction : public UItemFragment
{
	GENERATED_BODY()

public:
	virtual void OnEndPlay() override;
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp) override;

	virtual void DelayedAction() {}

	UPROPERTY(EditDefaultsOnly)
	float Delay;

	FTimerHandle DelayedActionHandle;
};
