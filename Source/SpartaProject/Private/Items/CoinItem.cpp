#include "CoinItem.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "SpartaGameMode.h"

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
		AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(this);
		ASpartaGameMode* SpartaGameMode = Cast<ASpartaGameMode>(GameModeBase);
		if (SpartaGameMode)
		{
			SpartaGameMode->CollectCoinAndAddScore(PointValue);
		}
		DestroyItem();
	}
}
