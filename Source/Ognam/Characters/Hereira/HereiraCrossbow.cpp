// Fill out your copyright notice in the Description page of Project Settings.

#include "HereiraCrossbow.h"
#include "HereiraCrossbowAction.h"

UHereiraCrossbow::UHereiraCrossbow()
{
	MaxAmmo = 3;
	Ammo = MaxAmmo;
	ReloadTime = 3.0f;
	WeaponActionClass = UHereiraCrossbowAction::StaticClass();
}
