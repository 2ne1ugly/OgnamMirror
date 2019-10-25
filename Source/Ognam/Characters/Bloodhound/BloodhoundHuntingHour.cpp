// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "BloodhoundHuntingHour.h"
#include "BloodhoundHuntingHourAction.h"

UBloodhoundHuntingHour::UBloodhoundHuntingHour()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 1.f;
}

void UBloodhoundHuntingHour::ActivateAbility()
{
	NewObject<UBloodhoundHuntingHourAction>(GetOwner())->RegisterComponent();
}
