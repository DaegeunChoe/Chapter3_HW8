//#pragma once
//
//#include "CoreMinimal.h"
//#include "BaseItem.h"
//#include "MineItem.generated.h"
//
//class USphereComponent;
//
//UCLASS()
//class SPARTAPROJECT_API AMineItem : public ABaseItem
//{
//	GENERATED_BODY()
//	
//public:
//	AMineItem();
//	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
//
//protected:
//	virtual void ActivateItem(AActor* Activator) override;
//	virtual void DestroyItem() override;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//	float ExplosionDelay;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//	float ExplosionRadius;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//	int32 ExplosionDamage;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
//	TObjectPtr<USphereComponent> ExplosionCollision;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effect")
//	TObjectPtr<UParticleSystem> ExplosionParticle;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effect")
//	TObjectPtr<USoundBase> ExplosionSound;
//
//	FTimerHandle ExplosionTimerHandle;
//	
//	void Explode();
//	bool bHasExploded;
//	
//	FTimerHandle DestroyExplodedParticleTimerHandle;
//	UParticleSystemComponent* ExplodedParticle;
//	void RemoveExplodedParticle();
//};
