#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "ItemFragment_AffectCharacter.generated.h"

UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class UAffectCharacterMethod : public UObject
{
	GENERATED_BODY()

public:
	virtual void Affect(AActor* Causer, ACharacter* Target) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	float Amount;
};

UCLASS()
class UDamageCharacterMethod : public UAffectCharacterMethod
{
	GENERATED_BODY()

public:
	virtual void Affect(AActor* Causer, ACharacter* Target) override;
};

UCLASS()
class UHealCharacterMethod : public UAffectCharacterMethod
{
	GENERATED_BODY()

public:
	virtual void Affect(AActor* Causer, ACharacter* Target) override;
};

UCLASS()
class UItemFragment_AffectCharacter : public UItemFragment
{
	GENERATED_BODY()

public:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp) override;

	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly)
	TObjectPtr<UAffectCharacterMethod> AffectMethod;
};
