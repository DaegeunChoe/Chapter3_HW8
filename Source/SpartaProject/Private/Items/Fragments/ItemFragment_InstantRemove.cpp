#include "Fragments/ItemFragment_InstantRemove.h"

void UItemFragment_InstantRemove::OnBeginPlay()
{
	if (ItemActor)
	{
		RemoveTimerHandle = ItemActor->GetWorldTimerManager().SetTimerForNextTick(
			this, &ThisClass::RemoveItemActor);
	}
}

void UItemFragment_InstantRemove::OnEndPlay()
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

void UItemFragment_InstantRemove::RemoveItemActor()
{
	if (IsValid(ItemActor))
	{
		ItemActor->Destroy();
	}
}
