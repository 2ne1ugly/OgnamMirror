// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "HazelPyromancy.h"
#include "HazelPyromancyAction.h"
#include "HazelPyromancyAimDown.h"

UHazelPyromancy::UHazelPyromancy()
{
	WeaponActionClass = UHazelPyromancyAction::StaticClass();
	bInfiniteAmmo = true;

	bBindSub = true;
	bCanAimDown = true;
	AimDownClass = UHazelPyromancyAimDown::StaticClass();
}

