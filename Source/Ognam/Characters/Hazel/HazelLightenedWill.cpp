// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "HazelLightenedWill.h"
#include "Ognam/OgnamCharacter.h"

UHazelLightenedWill::UHazelLightenedWill()
{
	AbilityType = EAbilityType::Mobility;
	bIsPassive = true;
}

void UHazelLightenedWill::BeginPlay()
{
	Super::BeginPlay();

	Target->BaseSpeed *= 1.15f;
}
