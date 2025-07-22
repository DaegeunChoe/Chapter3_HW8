#include "SpartaGameState.h"
#include "SpartaGameInstance.h"
#include "SpawnVolume.h"
#include "BaseItem.h"
#include "SpartaPlayerController.h"
#include "CoinItem.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

ASpartaGameState::ASpartaGameState()
{
	RemainTime = 0.0f;
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();
	RegisterDelegates();
}

void ASpartaGameState::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	UnregisterDelegates();
	Super::EndPlay(EndPlayReason);
}

void ASpartaGameState::SetCurrentLevelInfo(FGameStatistics GameStatistics)
{
	SetScore(GameStatistics.Score);
	SetCurrentLevel(GameStatistics.LevelIndex);
	SetCurrentWave(GameStatistics.WaveIndex);
	SetSpawnCoinCount(GameStatistics.SpawnedCoinCount);
	SetCollectedCoinCount(GameStatistics.CollectedCoinCount);
	SetRemainTime(GameStatistics.LevelDuration);
}

void ASpartaGameState::SetScore(int32 NewValue)
{
	GameStatistics.Score = NewValue;
	OnScoreChanged.Broadcast(NewValue);
}

void ASpartaGameState::SetCurrentLevel(int32 NewValue)
{
	GameStatistics.LevelIndex = NewValue;
	OnLevelChanged.Broadcast(NewValue);
}

void ASpartaGameState::SetCurrentWave(int32 NewValue)
{
	GameStatistics.WaveIndex = NewValue;
	OnWaveChanged.Broadcast(NewValue);
}

void ASpartaGameState::SetSpawnCoinCount(int32 NewValue)
{
	GameStatistics.SpawnedCoinCount = NewValue;
	OnSpawnCoinCountChanged.Broadcast(NewValue);
}

void ASpartaGameState::SetCollectedCoinCount(int32 NewValue)
{
	GameStatistics.CollectedCoinCount = NewValue;
	OnCollectedCoinCountChanged.Broadcast(NewValue);
}

void ASpartaGameState::SetRemainTime(float NewValue)
{
	RemainTime = FMath::Max(NewValue, 0.0f);
	OnRemainTimeChanged.Broadcast(RemainTime);
}

void ASpartaGameState::AddScore(int32 Amount)
{
	int32 NewScore = GameStatistics.Score + Amount;
	SetScore(NewScore);

	if (USpartaGameInstance* SpartaGameInstance = GetGameInstance<USpartaGameInstance>())
	{
		SpartaGameInstance->AddToScore(Amount);
	}
}

void ASpartaGameState::OnCollectCoin()
{
	int32 Increased = GameStatistics.CollectedCoinCount + 1;
	SetCollectedCoinCount(Increased);
}

bool ASpartaGameState::IsAllCoinCollected() const
{
	return (GameStatistics.SpawnedCoinCount > 0) && (GameStatistics.CollectedCoinCount >= GameStatistics.SpawnedCoinCount);
}

void ASpartaGameState::RegisterDelegates()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	check(PC);

	ASpartaPlayerController* SpartaPC = Cast<ASpartaPlayerController>(PC);
	check(SpartaPC);

	OnScoreChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateScore);
	OnLevelChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateLevel);
	//OnWaveChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateWave);
	//OnSpawnCoinCountChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateScore);
	//OnCollectedCoinCountChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateScore);
	OnRemainTimeChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateRemainTime);
}

void ASpartaGameState::UnregisterDelegates()
{
	OnScoreChanged.Clear();
	OnLevelChanged.Clear();
	OnWaveChanged.Clear();
	OnSpawnCoinCountChanged.Clear();
	OnCollectedCoinCountChanged.Clear();
	OnRemainTimeChanged.Clear();
}
