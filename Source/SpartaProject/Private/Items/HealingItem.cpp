#include "HealingItem.h"
#include "SpartaCharacter.h"

AHealingItem::AHealingItem()
{
	HealAmount = 20;
	ItemType = TEXT("Healing");
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	if (IsValid(Activator) && Activator->ActorHasTag(TEXT("Player")))
	{
		ASpartaCharacter* Sparta = Cast<ASpartaCharacter>(Activator);
		if (!IsValid(Sparta))
		{
			return;
		}
		Sparta->AddHealth(HealAmount);
		DestroyItem();
	}
}
