#include "OnlyOnceItem.h"

AOnlyOnceItem::AOnlyOnceItem()
{
	IsActivated = false;
}

void AOnlyOnceItem::OnItemBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (IsActivated)
	{
		return;
	}
	else
	{
		if (OtherActor->ActorHasTag(TEXT("Player")))
		{
			IsActivated = true;
			Super::OnItemBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
		}
	}
}
