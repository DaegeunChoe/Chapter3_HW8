#include "SpartaPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "SpartaGameState.h"
#include "SpartaGameMode.h"
#include "SpartaGameInstance.h"
#include "Components/TextBlock.h"
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

void ASpartaPlayerController::ShowMainMenu(bool bIsRestart)
{
	RemoveWidgetsFromParent();
	CreateSetAndAddWidgetToViewport(MainMenuWidgetClass, MainMenuWidgetInstance);

	if (MainMenuWidgetInstance)
	{
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}

	UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText")));

	if (bIsRestart)
	{
		SetRestart(ButtonText);
		SetResultAnimation();
	}
	else
	{
		SetStart(ButtonText);
	}
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

void ASpartaPlayerController::OnUpdateRemainTime(float NewRemainTime)
{
	if (HUDWidgetInstance)
	{
		if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("Time"))))
		{
			FText NewText = FText::FromString(FString::Printf(TEXT("Time: %.1f"), NewRemainTime));
			TimeText->SetText(NewText);
		}
	}
}

void ASpartaPlayerController::OnUpdateLevel(int32 NewLevel)
{
	if (HUDWidgetInstance)
	{
		if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidgetInstance->GetWidgetFromName(TEXT("Level"))))
		{
			FText NewText = FText::FromString(FString::Printf(TEXT("Level: %d"), NewLevel + 1));
			TimeText->SetText(NewText);
		}
	}
}

void ASpartaPlayerController::StartGame()
{
	// Called from WBP Blueprint Event Graph
	USpartaGameInstance* GameInstance = GetGameInstance<USpartaGameInstance>();
	check(GameInstance);

	GameInstance->InitializeNewGame();

	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this);
	check(GameModeBase);

	ASpartaGameMode* SpartaGameMode = Cast<ASpartaGameMode>(GameModeBase);
	check(SpartaGameMode);

	if (SpartaGameMode->MaxLevels > 0)
	{
		FName FirstLevelName = SpartaGameMode->LevelInfos[0].MapName;
		UGameplayStatics::OpenLevel(GetWorld(), FirstLevelName);
		SetPause(false);
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
		ShowMainMenu(false);
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

void ASpartaPlayerController::SetStart(UTextBlock* ButtonText)
{
	if (ButtonText)
	{
		ButtonText->SetText(FText::FromString(TEXT("Start")));
	}
}

void ASpartaPlayerController::SetRestart(UTextBlock* ButtonText)
{
	if (ButtonText)
	{
		ButtonText->SetText(FText::FromString(TEXT("Restart")));
	}
}

void ASpartaPlayerController::SetResultAnimation()
{
	UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
	if (PlayAnimFunc)
	{
		MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
	}
	if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("TotalScoreText"))))
	{
		if (USpartaGameInstance* GameInstance = GetGameInstance<USpartaGameInstance>())
		{
			int32 TotalScore = GameInstance->GetTotalScore();
			TotalScoreText->SetText(FText::FromString(FString::Printf(TEXT("Total Score: %d"), TotalScore)));
		}
	}
}
