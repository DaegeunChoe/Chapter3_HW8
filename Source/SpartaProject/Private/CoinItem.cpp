#include "CoinItem.h"
#include "Engine/World.h"
#include "SpartaGameState.h"

ACoinItem::ACoinItem()
{
	PointValue = 0;
	ItemType = TEXT("DefaultCoin");
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	if (IsValid(Activator) && Activator->ActorHasTag(TEXT("Player")))
	{
		UWorld* World = GetWorld();
		if (!IsValid(World))
		{
			return;
		}

		ASpartaGameState* GameState = World->GetGameState<ASpartaGameState>();
		if (!IsValid(GameState))
		{
			return;
		}
		GameState->AddScore(PointValue);
		GameState->OnCoinCollected();
		DestroyItem();
	}
}
