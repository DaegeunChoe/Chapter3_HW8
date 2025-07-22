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
	void ShowMainMenu(bool bIsRestart);

	UFUNCTION()
	void OnUpdateScore(int32 NewScore);

	UFUNCTION()
	void OnUpdateRemainTime(float NewRemainTime);

	UFUNCTION()
	void OnUpdateLevel(int32 NewLevel);

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void StartGame();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "HUD")
	TObjectPtr<UUserWidget> HUDWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "Menu")
	TObjectPtr<UUserWidget> MainMenuWidgetInstance;

protected:
	virtual void BeginPlay() override;

private:
	void RemoveWidgetsFromParent();
	void CreateSetAndAddWidgetToViewport(TSubclassOf<UUserWidget> WidgetClass, TObjectPtr<UUserWidget>& NewWidget);

	void SetStart(UTextBlock* ButtonText);
	void SetRestart(UTextBlock* ButtonText);
	void SetResultAnimation();
};
