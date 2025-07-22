#include "Fragments/ItemFragment_AffectGameState.h"
#include "Kismet/GameplayStatics.h"
#include "SpartaGameState.h"
#include "SpartaGameMode.h"

void UItemFragment_AffectGameState::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	if (ItemActor)
	{
		if (UWorld* World = ItemActor->GetWorld())
		{
			if (ASpartaGameState* GameState = World->GetGameState<ASpartaGameState>())
			{
				AffectMethod->Affect(ItemActor, GameState);
			}
		}
	}
}

void UAddScoreMethod::Affect(AActor* Causer, AGameState* GameState)
{
	if (ASpartaGameState* SpartaGameState = Cast<ASpartaGameState>(GameState))
	{
		if (ASpartaGameMode* SpartaGameMode = Cast<ASpartaGameMode>(SpartaGameState->AuthorityGameMode))
		{
			SpartaGameMode->CollectCoinAndAddScore(Amount);
		}
	}
}
