#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SpartaGameInstance.h"
#include "SpartaGameState.generated.h"

struct FGameStatistics;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInt32Changed, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTwoFloatChanged, float, NewValue0, float, NewValue1);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTwoInt32Changed, int32, NewValue0, int32, NewValue1);

UCLASS()
class SPARTAPROJECT_API ASpartaGameState : public AGameState
{
	GENERATED_BODY()

public:
	ASpartaGameState();
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	void SetCurrentLevelInfo(FGameStatistics GameStatistics);

	UFUNCTION(BlueprintPure)
	int32 GetScore() const { return GameStatistics.Score; }

	UFUNCTION(BlueprintPure)
	int32 GetCurrentLevel() const { return GameStatistics.LevelIndex; }

	UFUNCTION(BlueprintPure)
	int32 GetCurrentWave() const { return GameStatistics.WaveIndex; }

	UFUNCTION(BlueprintPure)
	int32 GetSpawnCoinCount() const { return GameStatistics.SpawnedCoinCount; }

	UFUNCTION(BlueprintPure)
	int32 GetCollectedCoinCount() const { return GameStatistics.CollectedCoinCount; }

	UFUNCTION(BlueprintPure)
	float GetRemainTime() const { return RemainTime; }

	UFUNCTION(BlueprintCallable)
	void SetScore(int32 NewValue);

	UFUNCTION(BlueprintCallable)
	void SetCurrentLevel(int32 NewValue);

	UFUNCTION(BlueprintCallable)
	void SetCurrentWave(int32 NewValue);

	UFUNCTION(BlueprintCallable)
	void SetSpawnCoinCount(int32 NewValue);

	UFUNCTION(BlueprintCallable)
	void SetCollectedCoinCount(int32 NewValue);

	UFUNCTION(BlueprintCallable)
	void SetWaveDuration(float NewValue);

	UFUNCTION(BlueprintCallable)
	void SetRemainTime(float NewValue);

	UFUNCTION(BlueprintCallable)
	void AddScore(int32 Amount);

	void OnCollectCoin();

	bool IsAllCoinCollected() const;

	FGameStatistics GameStatistics;

protected:
	float RemainTime;

	FOnInt32Changed OnScoreChanged;
	FOnTwoInt32Changed OnLevelWaveChanged;
	FOnTwoInt32Changed OnCoinCountChanged;
	FOnTwoFloatChanged OnRemainTimeChanged;

private:
	void RegisterDelegates();
	void UnregisterDelegates();
};
