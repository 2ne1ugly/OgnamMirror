// Fill out your copyright notice in the Description page of Project Settings.

#include "LangdonAutoRifle.h"
#include "LangdonAutoRifleAction.h"
#include "LangdonAutoRifleAimDown.h"

ULangdonAutoRifle::ULangdonAutoRifle()
{
	MaxAmmo = 15;
	Ammo = MaxAmmo;
	ReloadTime = 3.0f;
	bInfiniteAmmo = false; 
	WeaponActionClass = ULangdonAutoRifleAction::StaticClass();

	bBindSub = true;
	bCanAimDown = true;
	AimDownClass = ULangdonAutoRifleAimDown::StaticClass();
}
