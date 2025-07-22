#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpartaGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FGameStatistics
{
	GENERATED_BODY()

	int32 Score;
	int32 LevelIndex;
	int32 SpawnedCoinCount;
	int32 CollectedCoinCount;
	float LevelDuration;
	float PlayTime;
};

UCLASS()
class SPARTAPROJECT_API USpartaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USpartaGameInstance();

	void InitializeNewGame();

	UFUNCTION(BlueprintPure)
	int32 GetCurrentLevelIndex() const { return GameStatistics.LevelIndex; }

	UFUNCTION(BlueprintPure)
	int32 GetTotalScore() const { return GameStatistics.Score; }

	UFUNCTION(BlueprintPure)
	int32 GetSpawnedCoinCount() const { return GameStatistics.SpawnedCoinCount; }

	UFUNCTION(BlueprintPure)
	int32 GetCollectedCoinCount() const { return GameStatistics.CollectedCoinCount; }

	UFUNCTION(BlueprintPure)
	float GetTotalLevelDuration() const { return GameStatistics.LevelDuration; }

	UFUNCTION(BlueprintPure)
	float GetTotalPlayTime() const { return GameStatistics.PlayTime; }

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);

	UFUNCTION(BlueprintCallable)
	void SetupNextLevel();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	FGameStatistics GameStatistics;
};
