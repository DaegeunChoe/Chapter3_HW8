#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
struct FInputActionValue;

typedef TFunction<void()> CharacterAffectFunction;

struct CharacterEffect
{
	CharacterEffect(
		CharacterAffectFunction& Commit, CharacterAffectFunction& Revert, FTimerHandle Handle)
		: Commit(Commit), Revert(Revert), Handle(Handle) {};

	CharacterAffectFunction& Commit;
	CharacterAffectFunction& Revert;
	FTimerHandle Handle;
};

UCLASS()
class SPARTAPROJECT_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASpartaCharacter();

	UFUNCTION(BlueprintPure)
	float GetHealth() const;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void AddHealth(float Amout);

	void AddTimerEffect(FName EffectName, float Duration, CharacterAffectFunction Commit, CharacterAffectFunction Revert);
	bool HasTimerEffect(FName EffectName);

	float GetNormalSpeed() const { return NormalSpeed; }
	void SetNormalSpeed(float NewValue);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnDeath();

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void StartJump(const FInputActionValue& Value);
	
	UFUNCTION()
	void StopJump(const FInputActionValue& Value);
	
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	
	UFUNCTION()
	void StartSprint(const FInputActionValue& Value);
	
	UFUNCTION()
	void StopSprint(const FInputActionValue& Value);

	UFUNCTION()
	void UpdateHPWidget();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UWidgetComponent> HPWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	float NormalSpeed;
	float SprintSpeedMultiplier;

	TMap<FName, CharacterEffect> Effects;
};
