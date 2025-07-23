#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpartaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UUserWidget;
class UTextBlock;

UCLASS()
class SPARTAPROJECT_API ASpartaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASpartaPlayerController();

	UFUNCTION(BlueprintPure, Category = "HUD")
	UUserWidget* GetHUDWidget() const;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowGameHUD();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ShowMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ShowGameOver();

	UFUNCTION()
	void OnChangedWaveFeatures(FString FeatureString);

	UFUNCTION()
	void OnUpdateScore(int32 NewScore);

	UFUNCTION()
	void OnUpdateRemainTime(float NewRemainTime, float Duration);

	UFUNCTION()
	void OnUpdateLevelWave(int32 NewLevel, int32 NewWave);

	UFUNCTION()
	void OnUpdateCoinCount(int32 CollectedCount, int32 SpawnedCount);

	UFUNCTION()
	void OnUpdateHealth(float Health, float MaxHealth);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	TObjectPtr<UUserWidget> HUDWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	TObjectPtr<UUserWidget> MainMenuWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	TObjectPtr<UUserWidget> GameOverWidgetInstance;

protected:
	virtual void BeginPlay() override;

private:
	void RemoveWidgetsFromParent();
	void CreateSetAndAddWidgetToViewport(TSubclassOf<UUserWidget> WidgetClass, TObjectPtr<UUserWidget>& NewWidget);

	void SetResultAnimation();
};
