// Fill out your copyright notice in the Description page of Project Settings.


#include "AshaThrowingDaggers.h"
#include "AshaThrowingDaggersAction.h"

UAshaThrowingDaggers::UAshaThrowingDaggers()
{
	MaxAmmo = 8;
	Ammo = MaxAmmo;
	ReloadTime = 2.0f;
	bInfiniteAmmo = false;
	WeaponActionClass = UAshaThrowingDaggersAction::StaticClass();

	bBindSub = false;
	bCanAimDown = false;
	//AimDownClass = UAshaThrowingDaggers::StaticClass();
}