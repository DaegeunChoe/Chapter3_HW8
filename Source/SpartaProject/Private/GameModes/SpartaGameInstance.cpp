#include "SpartaGameInstance.h"

USpartaGameInstance::USpartaGameInstance()
{
	GameStatistics.Score = 0;
	GameStatistics.LevelIndex = 0;
	GameStatistics.WaveIndex = 0;
	GameStatistics.SpawnedCoinCount = 0;
	GameStatistics.CollectedCoinCount = 0;
	GameStatistics.WaveDuration = 0;
	GameStatistics.PlayTime = 0;
}

void USpartaGameInstance::InitializeNewGame()
{
	GameStatistics.Score = 0;
	GameStatistics.LevelIndex = 0;
	GameStatistics.WaveIndex = 0;
	GameStatistics.SpawnedCoinCount = 0;
	GameStatistics.CollectedCoinCount = 0;
	GameStatistics.WaveDuration = 0;
	GameStatistics.PlayTime = 0;
}

void USpartaGameInstance::AddToScore(int32 Amount)
{
	GameStatistics.Score += Amount;
}

void USpartaGameInstance::SetupNextLevel()
{
	GameStatistics.LevelIndex++;
}
