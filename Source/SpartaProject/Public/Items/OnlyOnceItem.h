#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "OnlyOnceItem.generated.h"

UCLASS()
class SPARTAPROJECT_API AOnlyOnceItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AOnlyOnceItem();

	virtual void OnItemBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	bool IsActivated;
};
