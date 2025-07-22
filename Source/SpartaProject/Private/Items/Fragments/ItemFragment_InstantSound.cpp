#include "Fragments/ItemFragment_InstantSound.h"
#include "Kismet/GameplayStatics.h"

void UItemFragment_InstantSound::OnBeginPlay()
{
	if (PickupSound && ItemActor)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, ItemActor->GetActorLocation());
	}
}
