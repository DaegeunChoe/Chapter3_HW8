#include "Fragments/ItemFragment_PickupSound.h"
#include "Kismet/GameplayStatics.h"

void UItemFragment_PickupSound::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	if (PickupSound && ItemActor)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, ItemActor->GetActorLocation());
	}
}
