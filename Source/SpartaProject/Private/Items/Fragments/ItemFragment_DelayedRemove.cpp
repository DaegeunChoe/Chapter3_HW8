#include "Fragments/ItemFragment_DelayedRemove.h"

void UItemFragment_DelayedRemove::DelayedAction()
{
	if (ItemActor)
	{
		ItemActor->GetWorldTimerManager().SetTimerForNextTick(
			[this] () 
			{
				if (IsValid(ItemActor))
				{
					ItemActor->Destroy();
				}
			}
		);
	}
}
