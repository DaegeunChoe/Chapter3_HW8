#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SpartaGameMode.generated.h"

class UGameInstance;
class ASpartaCharacter;

USTRUCT(BlueprintType)
struct FLevelInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemToSpawn = 40;
};

UCLASS()
class SPARTAPROJECT_API ASpartaGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASpartaGameMode();

	void NotifyDeathOfCharacter(ASpartaCharacter* Character);
	void CollectCoinAndAddScore(int32 CoinPoint);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TArray<FLevelInfo> LevelInfos;

	UPROPERTY(BlueprintReadOnly, Category = "Level")
	int32 MaxLevels;

protected:
	virtual void BeginPlay() override;

	void StartLevel();
	void EndLevel();
	void OnLevelTimeUp();
	void OnGameOver();

	FTimerHandle LevelTimerHandle;
};
