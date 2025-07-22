#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ItemFragment_PickupParticle.generated.h"

UCLASS()
class UItemFragment_PickupParticle : public UItemFragment
{
	GENERATED_BODY()

public:
	virtual void OnEndPlay();
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp) override;

	void RemoveParticle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UParticleSystem> PickupParticle;

	UParticleSystemComponent* Particle;
	FTimerHandle DestroyParticleTimerHandle;
	
};
