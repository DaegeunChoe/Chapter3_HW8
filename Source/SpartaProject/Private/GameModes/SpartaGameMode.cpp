#include "SpartaGameMode.h"
#include "SpartaGameState.h"
#include "SpartaGameInstance.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "BaseItem.h"
#include "CoinItem.h"

ASpartaGameMode::ASpartaGameMode()
{
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
	GameStateClass = ASpartaGameState::StaticClass();
	MaxLevels = 0;
}

void ASpartaGameMode::NotifyDeathOfCharacter(ASpartaCharacter* Character)
{
	OnGameOver();
}

void ASpartaGameMode::CollectCoinAndAddScore(int32 CoinPoint)
{
	if (ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>())
	{
		SpartaGameState->AddScore(CoinPoint);
		SpartaGameState->OnCollectCoin();

		if (SpartaGameState->IsAllCoinCollected())
		{
			EndLevel();
		}
	}
}

void ASpartaGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	MaxLevels = LevelInfos.Num();
	if (MaxLevels > 0)
	{
		StartLevel();
	}
}

void ASpartaGameMode::StartLevel()
{
	USpartaGameInstance* SpartaGameInstance = GetGameInstance<USpartaGameInstance>();
	if (SpartaGameInstance == nullptr)
	{
		return;
	}

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 TotalScsore = SpartaGameInstance->TotalScore;
	const int32 CurrentLevelIndex = SpartaGameInstance->CurrentLevelIndex;
	const int32 ItemToSpawn = LevelInfos[CurrentLevelIndex].ItemToSpawn;
	const float LevelDuration = LevelInfos[CurrentLevelIndex].Duration;

	int32 SpawnCoinCount = 0;
	for (int32 n = 0; n < ItemToSpawn; n++)
	{
		if (FoundVolumes.Num() > 0)
		{
			if (ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]))
			{
				ABaseItem* SpawnedItem = SpawnVolume->SpawnRandomItem();
				if (IsValid(SpawnedItem) && SpawnedItem->IsA(ACoinItem::StaticClass()))
				{
					SpawnCoinCount++;
				}
			}
		}
	}

	GetWorldTimerManager().SetTimer(LevelTimerHandle, this, &ASpartaGameMode::OnLevelTimeUp, LevelDuration, false);
	GetWorldTimerManager().SetTimer(RemainTimeUpdateHandle, this, &ThisClass::UpdateRemainTime, 0.1f, true);

	ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>();
	if (IsValid(SpartaGameState))
	{
		GetWorldTimerManager().SetTimerForNextTick([SpartaGameState, TotalScsore, CurrentLevelIndex, SpawnCoinCount, LevelDuration]()
			{
				SpartaGameState->SetCurrentLevelInfo(TotalScsore, CurrentLevelIndex, SpawnCoinCount, LevelDuration);
			});
	}
}

void ASpartaGameMode::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	GetWorldTimerManager().ClearTimer(RemainTimeUpdateHandle);

	USpartaGameInstance* SpartaGameInstance = GetGameInstance<USpartaGameInstance>();
	ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>();

	if (IsValid(SpartaGameInstance) && IsValid(SpartaGameState))
	{
		SpartaGameInstance->SetupNextLevel();
		int32 NextLevelIndex = SpartaGameInstance->CurrentLevelIndex;
		if (LevelInfos.IsValidIndex(NextLevelIndex))
		{
			UGameplayStatics::OpenLevel(GetWorld(), LevelInfos[NextLevelIndex].MapName);
		}
		else if (NextLevelIndex >= MaxLevels)
		{
			OnGameOver();
		}
		else // Invalid Level
		{
			OnGameOver();
		}
	}
}

void ASpartaGameMode::OnLevelTimeUp()
{
	EndLevel();
}

void ASpartaGameMode::OnGameOver()
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

void ASpartaGameMode::UpdateRemainTime()
{
	if (ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>())
	{
		if (RemainTimeUpdateHandle.IsValid())
		{
			float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
			SpartaGameState->SetRemainTime(RemainingTime);
		}
		
	}
}
