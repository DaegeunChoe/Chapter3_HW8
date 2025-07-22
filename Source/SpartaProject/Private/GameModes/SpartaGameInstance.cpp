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

void USpartaGameInstance::SetupNextLevel()
{
	GameStatistics.LevelIndex++;
}

void USpartaGameInstance::UpdateGameStatistics(const FGameStatistics WaveStatistics)
{
	GameStatistics.Score = WaveStatistics.Score; // GameState가 Total Score를 가지고 있음
	GameStatistics.SpawnedCoinCount += WaveStatistics.SpawnedCoinCount;
	GameStatistics.CollectedCoinCount += WaveStatistics.CollectedCoinCount;
	GameStatistics.WaveDuration += WaveStatistics.WaveDuration;
	GameStatistics.PlayTime += WaveStatistics.PlayTime;
}
