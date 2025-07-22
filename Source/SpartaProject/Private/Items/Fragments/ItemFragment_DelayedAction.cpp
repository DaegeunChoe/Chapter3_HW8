#include "Fragments/ItemFragment_DelayedAction.h"

void UItemFragment_DelayedAction::OnEndPlay()
{
	if (DelayedActionHandle.IsValid())
	{
		if (ItemActor)
		{
			ItemActor->GetWorldTimerManager().ClearTimer(DelayedActionHandle);
		}
	}
}

void UItemFragment_DelayedAction::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	if (ItemActor)
	{
		ItemActor->GetWorldTimerManager().SetTimer(
			DelayedActionHandle, this, &ThisClass::DelayedAction, Delay, false);
	}
}
