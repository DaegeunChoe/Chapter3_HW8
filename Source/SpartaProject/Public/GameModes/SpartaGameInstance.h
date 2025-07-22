#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SpartaGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FGameStatistics
{
	GENERATED_BODY()

	int32 Score = 0;
	int32 LevelIndex = 0;
	int32 WaveIndex = 0;
	int32 SpawnedCoinCount = 0;
	int32 CollectedCoinCount = 0;
	float WaveDuration = 0;
	float PlayTime = 0;
};

UCLASS()
class SPARTAPROJECT_API USpartaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	USpartaGameInstance();
	
	UFUNCTION(BlueprintCallable)
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
	float GetTotalWaveDuration() const { return GameStatistics.WaveDuration; }

	UFUNCTION(BlueprintPure)
	float GetTotalPlayTime() const { return GameStatistics.PlayTime; }

	UFUNCTION(BlueprintCallable)
	void SetupNextLevel();

	void UpdateGameStatistics(const FGameStatistics WaveStatistics);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	FGameStatistics GameStatistics;
};
