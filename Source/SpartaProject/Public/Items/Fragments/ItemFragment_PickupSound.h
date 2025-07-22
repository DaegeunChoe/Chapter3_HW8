#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ItemFragment_PickupSound.generated.h"

UCLASS()
class UItemFragment_PickupSound : public UItemFragment
{
	GENERATED_BODY()

public:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> PickupSound;
};
