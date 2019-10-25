// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "BloodhoundImpactShotgun.h"
#include "BloodhoundImpactShotgunAction.h"

UBloodhoundImpactShotgun::UBloodhoundImpactShotgun()
{
	AbilityType = EAbilityType::Special;
	Cooldown = 1.f;
}

void UBloodhoundImpactShotgun::ActivateAbility()
{
	NewObject<UBloodhoundImpactShotgunAction>(GetOwner())->RegisterComponent();
}
