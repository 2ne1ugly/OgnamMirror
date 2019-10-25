// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "JeraSuppressiveImpact.h"
#include "JeraSuppressiveImpactAction.h"
UJeraSuppressiveImpact::UJeraSuppressiveImpact()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 4.f;
}

void UJeraSuppressiveImpact::ActivateAbility()
{
	NewObject<UJeraSuppressiveImpactAction>(Target)->RegisterComponent();
}
