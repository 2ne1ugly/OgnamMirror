// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "HereiraCrossbow.h"
#include "HereiraCrossbowAction.h"

UHereiraCrossbow::UHereiraCrossbow()
{
	MaxAmmo = 3;
	Ammo = MaxAmmo;
	ReloadTime = 3.0f;
	WeaponActionClass = UHereiraCrossbowAction::StaticClass();
}

void UHereiraCrossbow::StatusEffectApplied(EStatusEffect StatusEffect)
{
}

void UHereiraCrossbow::ActionTaken(EActionNotifier ActionType)
{
	// Reloading cancelling system.
	if (bReloading)
	{
		if ((ActionType & EActionNotifier::Focus) != EActionNotifier::None)
		{
			InterruptReloading();
		}
	}
}
