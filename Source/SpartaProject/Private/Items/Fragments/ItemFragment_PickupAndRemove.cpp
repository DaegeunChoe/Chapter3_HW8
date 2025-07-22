#include "Fragments/ItemFragment_PickupAndRemove.h"

void UItemFragment_PickupAndRemove::OnEndPlay()
{
	if (RemoveTimerHandle.IsValid())
	{
		if (IsValid(ItemActor))
		{
			ItemActor->GetWorldTimerManager().ClearTimer(RemoveTimerHandle);
		}
		RemoveItemActor();
	}
}

void UItemFragment_PickupAndRemove::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	if (ItemActor)
	{
		RemoveTimerHandle = ItemActor->GetWorldTimerManager().SetTimerForNextTick(
			this, &ThisClass::RemoveItemActor);
	}
}

void UItemFragment_PickupAndRemove::RemoveItemActor()
{
	if (IsValid(ItemActor))
	{
		ItemActor->Destroy();
	}
}
