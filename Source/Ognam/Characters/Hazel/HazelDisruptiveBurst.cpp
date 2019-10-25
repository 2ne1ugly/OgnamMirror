// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "HazelDisruptiveBurst.h"
#include "HazelBurstAction.h"
#include "HazelEnhancedBurstAction.h"
#include "HazelBlazed.h"

UHazelDisruptiveBurst::UHazelDisruptiveBurst()
{
	AbilityType = EAbilityType::Special;
	Cooldown = 10.f;
}

void UHazelDisruptiveBurst::ActivateAbility()
{
	//Make this more smooth.
	if (Target->GetModifier<UHazelBlazed>())
	{
		NewObject<UHazelEnhancedBurstAction>(Target)->RegisterComponent();
	}
	else
	{
		NewObject<UHazelBurstAction>(Target)->RegisterComponent();
	}
}
