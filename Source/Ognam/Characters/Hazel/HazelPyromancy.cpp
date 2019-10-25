// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "HazelPyromancy.h"
#include "HazelPyromancyAction.h"

UHazelPyromancy::UHazelPyromancy()
{
	WeaponActionClass = UHazelPyromancyAction::StaticClass();
	bInfiniteAmmo = true;
}

