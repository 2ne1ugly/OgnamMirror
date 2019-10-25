// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "IsmaelLuxAeterna.h"
#include "IsmaelLuxDetonator.h"
#include "Engine/World.h"

UIsmaelLuxAeterna::UIsmaelLuxAeterna()
{
	AbilityType = EAbilityType::Mobility;
	Cooldown = 1.f;
}

void UIsmaelLuxAeterna::ActivateAbility()
{
	FVector Location = Target->GetActorLocation();
	FRotator Rotator = Target->GetActorForwardVector().Rotation();

	FActorSpawnParameters Params;
	Params.bNoFail = true;
	Params.Instigator = Target;

	AIsmaelLuxDetonator* Detonator = GetWorld()->SpawnActor<AIsmaelLuxDetonator>(Location, Rotator, Params);
	Detonator->SetReplicates(true);
}