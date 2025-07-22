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

void ASpartaGameState::SetCurrentLevelInfo(FGameStatistics NewGameStatistics)
{
	SetScore(NewGameStatistics.Score);
	SetCurrentLevel(NewGameStatistics.LevelIndex);
	SetCurrentWave(NewGameStatistics.WaveIndex);
	SetSpawnCoinCount(NewGameStatistics.SpawnedCoinCount);
	SetCollectedCoinCount(NewGameStatistics.CollectedCoinCount);
	SetWaveDuration(NewGameStatistics.WaveDuration);
	SetRemainTime(NewGameStatistics.WaveDuration);
}

void ASpartaGameState::SetScore(int32 NewValue)
{
	GameStatistics.Score = NewValue;
	OnScoreChanged.Broadcast(NewValue);
}

void ASpartaGameState::SetCurrentLevel(int32 NewValue)
{
	GameStatistics.LevelIndex = NewValue;
	OnLevelWaveChanged.Broadcast(NewValue, GameStatistics.WaveIndex);
}

void ASpartaGameState::SetCurrentWave(int32 NewValue)
{
	GameStatistics.WaveIndex = NewValue;
	OnLevelWaveChanged.Broadcast(GameStatistics.LevelIndex, NewValue);
}

void ASpartaGameState::SetSpawnCoinCount(int32 NewValue)
{
	GameStatistics.SpawnedCoinCount = NewValue;
	OnCoinCountChanged.Broadcast(GameStatistics.CollectedCoinCount, NewValue);
}

void ASpartaGameState::SetCollectedCoinCount(int32 NewValue)
{
	GameStatistics.CollectedCoinCount = NewValue;
	OnCoinCountChanged.Broadcast(NewValue, GameStatistics.SpawnedCoinCount);
}

void ASpartaGameState::SetWaveDuration(float NewValue)
{
	GameStatistics.WaveDuration = FMath::Max(NewValue, 0.0f);
	OnRemainTimeChanged.Broadcast(RemainTime, GameStatistics.WaveDuration);
}

void ASpartaGameState::SetRemainTime(float NewValue)
{
	RemainTime = FMath::Max(NewValue, 0.0f);
	GameStatistics.PlayTime = GameStatistics.WaveDuration - RemainTime;
	OnRemainTimeChanged.Broadcast(RemainTime, GameStatistics.WaveDuration);
}

void ASpartaGameState::AddScore(int32 Amount)
{
	int32 NewScore = GameStatistics.Score + Amount;
	SetScore(NewScore);
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
	OnLevelWaveChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateLevelWave);
	OnCoinCountChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateCoinCount);
	OnRemainTimeChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateRemainTime);
}

void ASpartaGameState::UnregisterDelegates()
{
	OnScoreChanged.Clear();
	OnLevelWaveChanged.Clear();
	OnCoinCountChanged.Clear();
	OnRemainTimeChanged.Clear();
}
