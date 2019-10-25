// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "JeraDescending.h"
#include "Ognam/OgnamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "JeraRadiantDiveDropPoint.h"

UJeraDescending::UJeraDescending()
{
	StatusEffect |= EStatusEffect::Unarmed | EStatusEffect::Silenced;
}

bool UJeraDescending::ShouldEnd()
{
	return !Target->GetCharacterMovement()->IsFalling();
}

void UJeraDescending::TickModifier(float DeltaTime)
{
	Target->AirControl += Target->BaseAirControl * 3;
	Target->Gravity += Target->BaseGravity / 2;
}

void UJeraDescending::EndModifier()
{
	if (!Target->IsAlive())
	{
		return;
	}
	if (Target->HasAuthority())
	{
		FActorSpawnParameters Params;
		Params.Instigator = Target;
		Params.bNoFail = true;
		GetWorld()->SpawnActor<AJeraRadiantDiveDropPoint>(Target->GetActorLocation(), FRotator::ZeroRotator, Params)->SetReplicates(true);
	}
}
