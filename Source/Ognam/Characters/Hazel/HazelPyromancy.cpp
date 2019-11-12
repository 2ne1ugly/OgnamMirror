// Fill out your copyright notice in the Description page of Project Settings.


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

