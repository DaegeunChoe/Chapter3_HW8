#include "SpikeItem.h"
#include "SpartaCharacter.h"

void ASpikeItem::OnItemBeginOverlap(
	UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(OtherActor))
	{
		FName EffectName = FName(TEXT("HitSpkie"));
		if (!SpartaCharacter->HasTimerEffect(EffectName))
		{
			Super::OnItemBeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

			SpartaCharacter->AddTimerEffect(EffectName, 2.0, []() {}, []() {});
		}
	}
}
