#include "SpartaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "SpartaGameState.h"
#include "SpartaGameMode.h"
#include "SpartaGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/RadialSlider.h"
#include "Kismet/GameplayStatics.h"

ASpartaPlayerController::ASpartaPlayerController()
	: InputMappingContext(nullptr),
	  MoveAction(nullptr),
	  JumpAction(nullptr),
	  LookAction(nullptr),
	  SprintAction(nullptr),
	  HUDWidgetClass(nullptr),
	  HUDWidgetInstance(nullptr),
	  MainMenuWidgetClass(nullptr),
	  MainMenuWidgetInstance(nullptr)
{
}

UUserWidget* ASpartaPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void ASpartaPlayerController::ShowGameHUD()
{
	RemoveWidgetsFromParent();
	CreateSetAndAddWidgetToViewport(HUDWidgetClass, HUDWidgetInstance);

	if (HUDWidgetInstance)
	{
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}

void ASpartaPlayerController::ShowMainMenu()
{
	RemoveWidgetsFromParent();
	CreateSetAndAddWidgetToViewport(MainMenuWidgetClass, MainMenuWidgetInstance);

	if (MainMenuWidgetInstance)
	{
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}

void ASpartaPlayerController::ShowGameOver()
{
	RemoveWidgetsFromParent();
	CreateSetAndAddWidgetToViewport(GameOverWidgetClass, GameOverWidgetInstance);

	if (GameOverWidgetInstance)
	{
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}

	SetResultAnimation();
}

void ASpartaPlayerController::OnUpdateScore(int32 NewScore)
{
	if (HUDWidgetInstance)
	{
		if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("Score"))))
		{
			FText NewText = FText::FromString(FString::Printf(TEXT("Score: %d"), NewScore));
			TimeText->SetText(NewText);
		}
	}
}

void ASpartaPlayerController::OnUpdateRemainTime(float NewRemainTime, float Duration)
{
	if (HUDWidgetInstance)
	{
		if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("Time"))))
		{
			FText NewText = FText::FromString(FString::Printf(TEXT("%.1f"), NewRemainTime));
			TimeText->SetText(NewText);
		}
		if (URadialSlider* Slider = Cast<URadialSlider>(HUDWidgetInstance->GetWidgetFromName(TEXT("TimeBar"))))
		{
			if (Duration > 0)
			{
				Slider->SetValue(NewRemainTime / Duration);
			}
		}
	}
}

void ASpartaPlayerController::OnUpdateLevelWave(int32 NewLevel, int32 NewWave)
{
	if (HUDWidgetInstance)
	{
		if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("Level"))))
		{
			int32 Level = NewLevel + 1;
			int32 Wave = NewWave + 1;
			FText NewText = FText::FromString(FString::Printf(TEXT("Level: %d-%d"), Level, Wave));
			TimeText->SetText(NewText);
		}
	}
}

void ASpartaPlayerController::OnUpdateCoinCount(int32 CollectedCount, int32 SpawnedCount)
{
	if (HUDWidgetInstance)
	{
		if (UTextBlock* CoinText = Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("Coin"))))
		{
			FText NewText = FText::FromString(FString::Printf(TEXT("Coin: %d/%d"), CollectedCount, SpawnedCount));
			CoinText->SetText(NewText);
		}
	}
}

void ASpartaPlayerController::OnUpdateHealth(float Health, float MaxHealth)
{
	if (HUDWidgetInstance)
	{
		if (UTextBlock* HPText = Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("HP"))))
		{
			FText NewText = FText::FromString(FString::Printf(TEXT("HP %.0f"), Health));
			HPText->SetText(NewText);
		}
		if (UProgressBar* HPBar = Cast<UProgressBar>(HUDWidgetInstance->GetWidgetFromName(TEXT("HPBar"))))
		{
			if (MaxHealth > 0)
			{
				HPBar->SetPercent(Health / MaxHealth);
			}
		}
	}
}

void ASpartaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	check(LocalPlayer);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	if (InputMappingContext)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains(TEXT("MenuLevel")))
	{
		ShowMainMenu();
	}
	else
	{
		ShowGameHUD();
	}
}

void ASpartaPlayerController::RemoveWidgetsFromParent()
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}
	if (GameOverWidgetInstance)
	{
		GameOverWidgetInstance->RemoveFromParent();
		GameOverWidgetInstance = nullptr;
	}
}

void ASpartaPlayerController::CreateSetAndAddWidgetToViewport(TSubclassOf<UUserWidget> WidgetClass, TObjectPtr<UUserWidget>& NewWidget)
{
	if (WidgetClass)
	{
		NewWidget = CreateWidget<UUserWidget>(this, WidgetClass);
		if (NewWidget)
		{
			(NewWidget)->AddToViewport();
		}
	}
}

void ASpartaPlayerController::SetResultAnimation()
{
	if (GameOverWidgetInstance)
	{
		if (USpartaGameInstance* GameInstance = GetGameInstance<USpartaGameInstance>())
		{
			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(GameOverWidgetInstance->GetWidgetFromName(TEXT("TotalScoreText"))))
			{
				int32 TotalScore = GameInstance->GetTotalScore();
				FText NewText = FText::FromString(FString::Printf(TEXT("Total Score: %d"), TotalScore));
				TotalScoreText->SetText(NewText);
			}
			if (UTextBlock* TotalCoinText = Cast<UTextBlock>(GameOverWidgetInstance->GetWidgetFromName(TEXT("TotalCoinText"))))
			{
				int32 Spawned = GameInstance->GetSpawnedCoinCount();
				int32 Collected = GameInstance->GetCollectedCoinCount();
				FText NewText = FText::FromString(FString::Printf(TEXT("Coins: %d/%d"), Collected, Spawned));
				TotalCoinText->SetText(NewText);
			}
			if (UTextBlock* TotalPlayTimeText = Cast<UTextBlock>(GameOverWidgetInstance->GetWidgetFromName(TEXT("TotalPlayTimeText"))))
			{
				float  TotalPlayTime = GameInstance->GetTotalPlayTime();
				FText NewText = FText::FromString(FString::Printf(TEXT("PlayTime: %.2f"), TotalPlayTime));
				TotalPlayTimeText->SetText(NewText);
			}
		}
	}
}
