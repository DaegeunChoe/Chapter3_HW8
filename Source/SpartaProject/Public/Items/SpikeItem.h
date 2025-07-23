#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "SpikeItem.generated.h"

UCLASS()
class SPARTAPROJECT_API ASpikeItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	virtual void OnItemBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
};
