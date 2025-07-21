#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SpartaGameState.generated.h"

UCLASS()
class SPARTAPROJECT_API ASpartaGameState : public AGameState
{
	GENERATED_BODY()

public:
	ASpartaGameState();

	void SetCurrentLevelInfo(int CoinCount);

	UFUNCTION(BlueprintPure)
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable)
	void AddScore(int32 Amount);

	void OnCollectCoin();

	bool IsAllCoinCollected() const;


protected:
	UPROPERTY(BlueprintReadWrite, Category = "Score")
	int32 Score;

	UPROPERTY(BlueprintReadOnly, Category = "Coin")
	int32 SpawnCoinCount;

	UPROPERTY(BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;
};
