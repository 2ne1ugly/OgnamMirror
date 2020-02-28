// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellSniperRifle.h"
#include "Ognam/OgnamCharacter.h"
#include "MaxwellSniperRifleAction.h"
#include "MaxwellSniperRifleAimDown.h"
UMaxwellSniperRifle::UMaxwellSniperRifle()
{
	MaxAmmo = 6;
	Ammo = MaxAmmo;
	//RoundsPerSecond = 2.5f;
	ReloadTime = 2.0f;

	bBindSub = true;
	WeaponActionClass = UMaxwellSniperRifleAction::StaticClass();

	bCanAimDown = true;
	AimDownClass = UMaxwellSniperRifleAimDown::StaticClass();
}
