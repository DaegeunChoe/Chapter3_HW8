#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ItemFragment_InstantParticle.generated.h"

UCLASS()
class UItemFragment_InstantParticle : public UItemFragment
{
	GENERATED_BODY()

public:
	virtual void OnBeginPlay() override;
	virtual void OnEndPlay();
	
	void RemoveParticle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UParticleSystem> PickupParticle;

	UParticleSystemComponent* Particle;
	FTimerHandle DestroyParticleTimerHandle;
};
