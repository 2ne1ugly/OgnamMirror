// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "HazelFlameBlast.h"
#include "HazelFlameBlastAction.h"

UHazelFlameBlast::UHazelFlameBlast()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 6.f;
}

void UHazelFlameBlast::ActivateAbility()
{
	NewObject<UHazelFlameBlastAction>(Target)->RegisterComponent();
}
