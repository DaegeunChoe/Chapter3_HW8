#include "SpartaGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "BaseItem.h"
#include "SpartaGameInstance.h"
#include "SpartaPlayerController.h"
#include "CoinItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

ASpartaGameState::ASpartaGameState()
{
	Score = 0;
	SpawnCoinCount = 0;
	CollectedCoinCount = 0;
}

void ASpartaGameState::SetCurrentLevelInfo(int CoinCount)
{
	Score = 0;
	SpawnCoinCount = CoinCount;
	CollectedCoinCount = 0;
}

int32 ASpartaGameState::GetScore() const
{
	return Score;
}

void ASpartaGameState::AddScore(int32 Amount)
{
	Score += Amount;

	if (USpartaGameInstance* SpartaGameInstance = GetGameInstance<USpartaGameInstance>())
	{
		SpartaGameInstance->AddToScore(Amount);
	}
}

void ASpartaGameState::OnCollectCoin()
{
	CollectedCoinCount += 1;
	UE_LOG(LogTemp, Warning, TEXT("OnCoinCollected %d/%d"), CollectedCoinCount, SpawnCoinCount);
}

bool ASpartaGameState::IsAllCoinCollected() const
{
	return (SpawnCoinCount > 0) && (CollectedCoinCount >= SpawnCoinCount);
}

/*
void StartLevel()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!IsValid(PC))
	{
		return;
	}
	ASpartaPlayerController* SpartaPC = Cast<ASpartaPlayerController>(PC);
	if (!IsValid(SpartaPC))
	{
		return;
	}
	SpartaPC->ShowGameHUD();

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance == nullptr)
	{
		return;
	}
	USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
	if (SpartaGameInstance == nullptr)
	{
		return;
	}
	CurrentLevelIndex = SpartaGameInstance->CurrentLevelIndex;

	SpawnCoinCount = 0;
	CollectedCoinCount = 0;

	// 현재 월드 검사
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 40;
	for (int32 n = 0; n < ItemToSpawn; n++)
	{
		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (!IsValid(SpawnVolume))
			{
				return;
			}
			ABaseItem* SpawnedItem = SpawnVolume->SpawnRandomItem();
			if (IsValid(SpawnedItem) && SpawnedItem->IsA(ACoinItem::StaticClass()))
			{
				SpawnCoinCount++;
			}
		}
	}
	
	// 타이머
	GetWorldTimerManager().SetTimer(LevelTimerHandle, this, &ASpartaGameState::OnLevelTimeUp, LevelDuration, false);

	UE_LOG(LogTemp, Warning, TEXT("Level %d Start!, Spawned %d Coins"), CurrentLevelIndex + 1, SpawnCoinCount);
	UE_LOG(LogTemp, Warning, TEXT("Current Total Score is %d"), SpartaGameInstance->TotalScore);
}

void EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	CurrentLevelIndex++;

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance == nullptr)
	{
		return;
	}
	USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
	if (SpartaGameInstance == nullptr)
	{
		return;
	}
	SpartaGameInstance->CurrentLevelIndex = CurrentLevelIndex;

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}

	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}

void ASpartaGameState::OnGameOver()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!IsValid(PC))
	{
		return;
	}
	ASpartaPlayerController* SpartaPC = Cast<ASpartaPlayerController>(PC);
	if (!IsValid(SpartaPC))
	{
		return;
	}
	SpartaPC->SetPause(true);
	SpartaPC->ShowMainMenu(true);
}


void OnLevelTimeUp()
{
	EndLevel();
}


void ASpartaGameState::UpdateHUD()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
	{
		return;
	}
	APlayerController* PC = World->GetFirstPlayerController();
	if (!IsValid(PC))
	{
		return;
	}
	ASpartaPlayerController* SpartaPC = Cast<ASpartaPlayerController>(PC);
	if (!IsValid(SpartaPC))
	{
		return;
	}
	UUserWidget* HUDWidget = SpartaPC->GetHUDWidget();
	if (!IsValid(HUDWidget))
	{
		return;
	}

	UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time")));
	if (!IsValid(TimeText))
	{
		return;
	}
	float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
	TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));

	UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score")));
	if (!IsValid(ScoreText))
	{
		return;
	}
	UGameInstance* GameInstance = GetGameInstance();
	if (!IsValid(GameInstance))
	{
		return;
	}
	USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
	if (!IsValid(SpartaGameInstance))
	{
		return;
	}
	int32 TotalScore = SpartaGameInstance->TotalScore;
	ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), TotalScore)));

	UTextBlock* LevelText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level")));
	if (!IsValid(LevelText))
	{
		return;
	}
	int32 LevelIndex = SpartaGameInstance->CurrentLevelIndex;
	LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), LevelIndex + 1)));
}

void ASpartaGameState::OnCoinCollected()
{
	CollectedCoinCount++;
	UE_LOG(LogTemp, Warning, TEXT("OnCoinCollected %d/%d"), CollectedCoinCount, SpawnCoinCount);

	if ((SpawnCoinCount > 0) && (CollectedCoinCount >= SpawnCoinCount))
	{
		EndLevel();
	}
}
*/