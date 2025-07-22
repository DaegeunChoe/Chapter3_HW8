#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

class USceneComponent;
class USphereComponent;
class UStaticMeshComponent;

UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class UItemFragment : public UObject
{
	GENERATED_BODY()

public:
	virtual void OnBeginPlay() {};
	virtual void OnEndPlay() {};
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp) {}
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp) {}
	
	void SetItemActor(ABaseItem* InItemActor)
	{
		ItemActor = InItemActor;
	}

	ABaseItem* ItemActor;
};

UCLASS()
class SPARTAPROJECT_API ABaseItem : public AActor
{
	GENERATED_BODY()

public:
	ABaseItem();
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	FName GetItemType() const { return TypeName; }

	UFUNCTION()
	virtual void OnItemBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display)
	FName TypeName;

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = Display)
	TArray<TObjectPtr<UItemFragment>> Fragments;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Itme|Component")
	TObjectPtr<USceneComponent> SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Itme|Component")
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Itme|Component")
	TObjectPtr<UStaticMeshComponent> StaticMesh;
};

/*
UCLASS()
class SPARTAPROJECT_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseItem();
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason);

protected:
	virtual void OnItemBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void OnItemEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void ActivateItem(AActor* Activator);
	virtual FName GetItemType() const;

	virtual void DestroyItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Itme|Component")
	TObjectPtr<USceneComponent> SceneComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Itme|Component")
	TObjectPtr<USphereComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Itme|Component")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effect")
	TObjectPtr<UParticleSystem> PickupParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effect")
	TObjectPtr<USoundBase> PickupSound;

	UParticleSystemComponent* Particle;
	FTimerHandle DestroyParticleTimerHandle;
	void RemoveParticle();
};
*/
