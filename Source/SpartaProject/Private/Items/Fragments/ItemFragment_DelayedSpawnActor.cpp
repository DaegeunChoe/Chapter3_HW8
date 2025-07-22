#include "Fragments/ItemFragment_DelayedSpawnActor.h"

void UItemFragment_DelayedSpawnActor::DelayedAction()
{
	if (ActorClassToSpawn)
	{
		if (ItemActor)
		{
			if (UWorld* World = ItemActor->GetWorld())
			{
				FActorSpawnParameters SpawnParams;
				FVector SpawnLocation = ItemActor->GetActorLocation();
				FRotator SpawnRotator = ItemActor->GetActorRotation();
				AActor* SpawnedActor = World->SpawnActor<AActor>(ActorClassToSpawn, SpawnLocation, SpawnRotator, SpawnParams);
			}
		}
	}
}
