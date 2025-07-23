#include "SpartaGameMode.h"
#include "SpartaGameState.h"
#include "SpartaGameInstance.h"
#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "BaseItem.h"

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
			EndWave();
		}
	}
}

void ASpartaGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	MaxLevels = LevelInfos.Num();

	FString CurrentMapName = GetWorld()->GetMapName();
	if (!CurrentMapName.Contains(TEXT("MenuLevel")))
	{
		if (MaxLevels > 0)
		{
			GetWorldTimerManager().SetTimerForNextTick([this]() { StartLevel(); });
			//StartLevel();
		}
	}
}

void ASpartaGameMode::StartLevel()
{
	StartWave();
}

void ASpartaGameMode::EndLevel()
{
	USpartaGameInstance* SpartaGameInstance = GetGameInstance<USpartaGameInstance>();
	ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>();

	if (IsValid(SpartaGameInstance) && IsValid(SpartaGameState))
	{
		SpartaGameInstance->SetupNextLevel();
		int32 NextLevelIndex = SpartaGameInstance->GetCurrentLevelIndex();
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

void ASpartaGameMode::StartWave()
{
	USpartaGameInstance* SpartaGameInstance = GetGameInstance<USpartaGameInstance>();
	if (SpartaGameInstance == nullptr)
	{
		return;
	}

	ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>();
	if (!IsValid(SpartaGameState))
	{
		return;
	}

	const int32 TotalScsore = SpartaGameInstance->GetTotalScore();
	const int32 CurrentLevelIndex = SpartaGameInstance->GetCurrentLevelIndex();
	const int32 CurrentWaveIndex = SpartaGameState->GetCurrentWave();

	const int32 ItemToSpawn = LevelInfos[CurrentLevelIndex].Waves[CurrentWaveIndex].ItemToSpawn;
	const float WaveDuration = LevelInfos[CurrentLevelIndex].Waves[CurrentWaveIndex].Duration;

	int32 SpawnCoinCount = 0;
	SpawnItems(ItemToSpawn, SpawnCoinCount);
	ActivateWaveFeatures(LevelInfos[CurrentLevelIndex].Waves[CurrentWaveIndex].FeaturesToActive);

	GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &ASpartaGameMode::OnWaveTimeUp, WaveDuration, false);
	GetWorldTimerManager().SetTimer(RemainTimeUpdateHandle, this, &ThisClass::UpdateRemainTime, 0.1f, true);

	GetWorldTimerManager().SetTimerForNextTick(
		[SpartaGameState, TotalScsore, CurrentLevelIndex, CurrentWaveIndex, SpawnCoinCount, WaveDuration]()
		{
			FGameStatistics NewGameStatistics;
			NewGameStatistics.Score = TotalScsore;
			NewGameStatistics.LevelIndex = CurrentLevelIndex;
			NewGameStatistics.WaveIndex = CurrentWaveIndex;
			NewGameStatistics.SpawnedCoinCount = SpawnCoinCount;
			NewGameStatistics.CollectedCoinCount = 0;
			NewGameStatistics.WaveDuration = WaveDuration;
			NewGameStatistics.PlayTime = 0;
			SpartaGameState->SetCurrentLevelInfo(NewGameStatistics);
		});
}

void ASpartaGameMode::EndWave()
{
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);
	GetWorldTimerManager().ClearTimer(RemainTimeUpdateHandle);


	USpartaGameInstance* SpartaGameInstance = GetGameInstance<USpartaGameInstance>();
	ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>();

	if (IsValid(SpartaGameInstance) && IsValid(SpartaGameState))
	{
		SpartaGameState->GameStatistics.PlayTime = SpartaGameState->GameStatistics.WaveDuration;

		SpartaGameInstance->UpdateGameStatistics(SpartaGameState->GameStatistics);

		int32 CurrentLevelIndex = SpartaGameState->GetCurrentLevel();
		int32 NextWaveIndex = SpartaGameState->GetCurrentWave() + 1;
		SpartaGameState->SetCurrentWave(NextWaveIndex);
		if (LevelInfos.IsValidIndex(CurrentLevelIndex) && LevelInfos[CurrentLevelIndex].Waves.IsValidIndex(NextWaveIndex))
		{
			ClearWave();
			StartWave();
		}
		else 
		{
			EndLevel();
		}
	}
}

void ASpartaGameMode::SpawnItems(int32 ItemToSpawn, int32& SpawnCoinCount)
{
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	for (int32 n = 0; n < ItemToSpawn; n++)
	{
		if (FoundVolumes.Num() > 0)
		{
			if (ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]))
			{
				ABaseItem* SpawnedItem = SpawnVolume->SpawnRandomItem();
				if (IsValid(SpawnedItem) && SpawnedItem->GetItemType() == FName(TEXT("Coin")))
				{
					SpawnCoinCount++;
				}
			}
		}
	}
}

void ASpartaGameMode::ClearWave()
{
	TArray<AActor*> FoundItems;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABaseItem::StaticClass(), FoundItems);

	for (int32 n = 0; n < FoundItems.Num(); n++)
	{
		FoundItems[n]->Destroy();
	}
}

void ASpartaGameMode::ActivateWaveFeatures(TArray<FName> Features)
{
	if (Features.Contains(FName(TEXT("Spike"))))
	{
		SpawnSpike(10);
	}
	if (Features.Contains(FName(TEXT("Explosion"))))
	{

	}
}

void ASpartaGameMode::SpawnSpike(int32 ItemToSpawn)
{
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	for (int32 n = 0; n < ItemToSpawn; n++)
	{
		if (FoundVolumes.Num() > 0)
		{
			if (ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]))
			{
				ABaseItem* SpawnedItem = SpawnVolume->SpawnSpikeItem();
			}
		}
	}
}

void ASpartaGameMode::SpawnExplosion()
{
}

void ASpartaGameMode::OnWaveTimeUp()
{
	EndWave();
}

void ASpartaGameMode::OnGameOver()
{
	USpartaGameInstance* SpartaGameInstance = GetGameInstance<USpartaGameInstance>();
	ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>();

	if (IsValid(SpartaGameInstance) && IsValid(SpartaGameState))
	{
		SpartaGameInstance->UpdateGameStatistics(SpartaGameState->GameStatistics);
	}

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
	SpartaPC->ShowGameOver();
}

void ASpartaGameMode::UpdateRemainTime()
{
	if (ASpartaGameState* SpartaGameState = GetGameState<ASpartaGameState>())
	{
		if (RemainTimeUpdateHandle.IsValid())
		{
			float RemainingTime = GetWorldTimerManager().GetTimerRemaining(WaveTimerHandle);
			SpartaGameState->SetRemainTime(RemainingTime);
		}
		
	}
}
