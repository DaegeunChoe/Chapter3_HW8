#include "Fragments/ItemFragment_AffectCharacter.h"
#include "SpartaCharacter.h"
#include "Kismet/GameplayStatics.h"

void UItemFragment_AffectCharacter::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		if (AffectMethod)
		{
			AffectMethod->Affect(ItemActor, Character);
		}
	}
}

void UDamageCharacterMethod::Affect(AActor* Causer, ACharacter* Target)
{
	UGameplayStatics::ApplyDamage(Target, Amount, nullptr, Causer, UDamageType::StaticClass());
}

void UHealCharacterMethod::Affect(AActor* Causer, ACharacter* Target)
{
	if (ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(Target))
	{
		SpartaCharacter->AddHealth(Amount);
	}
}
