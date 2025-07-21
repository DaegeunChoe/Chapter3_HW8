#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SpartaGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInt32Changed, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFloatChanged, float, NewValue);

UCLASS()
class SPARTAPROJECT_API ASpartaGameState : public AGameState
{
	GENERATED_BODY()

public:
	ASpartaGameState();
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	void SetCurrentLevelInfo(int32 TotalScore, int32 Level, int32 CoinCount, float Duration);

	UFUNCTION(BlueprintPure)
	int32 GetScore() const { return Score; }

	UFUNCTION(BlueprintPure)
	int32 GetCurrentLevel() const { return CurrentLevel; }

	UFUNCTION(BlueprintPure)
	int32 GetSpawnCoinCount() const { return SpawnCoinCount; }

	UFUNCTION(BlueprintPure)
	int32 GetCollectedCoinCount() const { return CollectedCoinCount; }

	UFUNCTION(BlueprintPure)
	float GetRemainTime() const { return RemainTime; }

	UFUNCTION(BlueprintCallable)
	void SetScore(int32 NewValue);

	UFUNCTION(BlueprintCallable)
	void SetCurrentLevel(int32 NewValue);

	UFUNCTION(BlueprintCallable)
	void SetSpawnCoinCount(int32 NewValue);

	UFUNCTION(BlueprintCallable)
	void SetCollectedCoinCount(int32 NewValue);

	UFUNCTION(BlueprintCallable)
	void SetRemainTime(float NewValue);

	UFUNCTION(BlueprintCallable)
	void AddScore(int32 Amount);

	void OnCollectCoin();

	bool IsAllCoinCollected() const;

protected:
	int32 Score;
	int32 CurrentLevel;
	int32 SpawnCoinCount;
	int32 CollectedCoinCount;
	float RemainTime;

	FOnInt32Changed OnScoreChanged;
	FOnInt32Changed OnLevelChanged;
	FOnInt32Changed OnSpawnCoinCountChanged;
	FOnInt32Changed OnCollectedCoinCountChanged;
	FOnFloatChanged OnRemainTimeChanged;

private:
	void RegisterDelegates();
	void UnregisterDelegates();
};
