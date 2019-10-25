// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "BloodhoundWithhold.h"
#include "BloodhoundWithholdAction.h"

UBloodhoundWithhold::UBloodhoundWithhold()
{
	AbilityType = EAbilityType::Utility;

	Cooldown = 9.f;
}

void UBloodhoundWithhold::ActivateAbility()
{
	NewObject<UBloodhoundWithholdAction>(Target)->RegisterComponent();
}
