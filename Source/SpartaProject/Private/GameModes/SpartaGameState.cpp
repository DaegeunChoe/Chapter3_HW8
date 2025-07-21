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
	Score = 0;
	CurrentLevel = 0;
	SpawnCoinCount = 0;
	CollectedCoinCount = 0;
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
	SetSpawnCoinCount(GameStatistics.SpawnedCoinCount);
	SetCollectedCoinCount(GameStatistics.CollectedCoinCount);
	SetRemainTime(GameStatistics.LevelDuration);
}

void ASpartaGameState::SetScore(int32 NewValue)
{
	Score = NewValue;
	OnScoreChanged.Broadcast(Score);
}

void ASpartaGameState::SetCurrentLevel(int32 NewValue)
{
	CurrentLevel = NewValue;
	OnLevelChanged.Broadcast(CurrentLevel);
}

void ASpartaGameState::SetSpawnCoinCount(int32 NewValue)
{
	SpawnCoinCount = NewValue;
	OnSpawnCoinCountChanged.Broadcast(SpawnCoinCount);
}

void ASpartaGameState::SetCollectedCoinCount(int32 NewValue)
{
	CollectedCoinCount = NewValue;
	OnCollectedCoinCountChanged.Broadcast(CollectedCoinCount);
}

void ASpartaGameState::SetRemainTime(float NewValue)
{
	RemainTime = FMath::Max(NewValue, 0.0f);
	OnRemainTimeChanged.Broadcast(RemainTime);
}

void ASpartaGameState::AddScore(int32 Amount)
{
	int32 NewScore = Score + Amount;
	SetScore(NewScore);

	if (USpartaGameInstance* SpartaGameInstance = GetGameInstance<USpartaGameInstance>())
	{
		SpartaGameInstance->AddToScore(Amount);
	}
}

void ASpartaGameState::OnCollectCoin()
{
	int32 Increased = CollectedCoinCount + 1;
	SetCollectedCoinCount(Increased);

	UE_LOG(LogTemp, Warning, TEXT("OnCoinCollected %d/%d"), CollectedCoinCount, SpawnCoinCount);
}

bool ASpartaGameState::IsAllCoinCollected() const
{
	return (SpawnCoinCount > 0) && (CollectedCoinCount >= SpawnCoinCount);
}

void ASpartaGameState::RegisterDelegates()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	check(PC);

	ASpartaPlayerController* SpartaPC = Cast<ASpartaPlayerController>(PC);
	check(SpartaPC);

	OnScoreChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateScore);
	OnLevelChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateLevel);
	//OnSpawnCoinCountChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateScore);
	//OnCollectedCoinCountChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateScore);
	OnRemainTimeChanged.AddDynamic(SpartaPC, &ASpartaPlayerController::OnUpdateRemainTime);
}

void ASpartaGameState::UnregisterDelegates()
{
	OnScoreChanged.Clear();
	OnLevelChanged.Clear();
	OnSpawnCoinCountChanged.Clear();
	OnCollectedCoinCountChanged.Clear();
	OnRemainTimeChanged.Clear();
}
