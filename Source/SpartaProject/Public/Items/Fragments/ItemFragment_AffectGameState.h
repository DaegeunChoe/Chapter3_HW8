#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ItemFragment_AffectGameState.generated.h"

class AGameState;

UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class UAffectGameStateMethod : public UObject
{
	GENERATED_BODY()

public:
	virtual void Affect(AActor* Causer, AGameState* GameState) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	float Amount;
};

UCLASS()
class UAddScoreMethod : public UAffectGameStateMethod
{
	GENERATED_BODY()

public:
	virtual void Affect(AActor* Causer, AGameState* GameState) override;
};

UCLASS()
class UItemFragment_AffectGameState : public UItemFragment
{
	GENERATED_BODY()

public:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp) override;

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly)
	TObjectPtr<UAffectGameStateMethod> AffectMethod;
};
