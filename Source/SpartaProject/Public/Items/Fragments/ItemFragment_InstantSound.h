#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ItemFragment_InstantSound.generated.h"

UCLASS()
class UItemFragment_InstantSound : public UItemFragment
{
	GENERATED_BODY()

public:
	virtual void OnBeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> PickupSound;
};
