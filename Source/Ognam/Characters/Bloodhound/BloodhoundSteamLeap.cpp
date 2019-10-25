// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "BloodhoundSteamLeap.h"
#include "BloodhoundSteamLeapAction.h"

UBloodhoundSteamLeap::UBloodhoundSteamLeap()
{
	AbilityType = EAbilityType::Mobility;
}

void UBloodhoundSteamLeap::ActivateAbility()
{
	NewObject<UBloodhoundSteamLeapAction>(GetOwner())->RegisterComponent();
}
