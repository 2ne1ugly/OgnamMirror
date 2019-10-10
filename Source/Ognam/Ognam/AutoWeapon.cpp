// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoWeapon.h"
#include "WeaponActionModifier.h"

UAutoWeapon::UAutoWeapon()
{
}

void UAutoWeapon::BasicPressed()
{
	if (!CanBasic())
	{
		if (Ammo == 0)
		{
			ReloadPressed();
		}
		return;
	}
	ServerBasicPressed();
}

void UAutoWeapon::BasicReleased()
{
	ServerBasicReleased();
}

void UAutoWeapon::ServerBasicPressed_Implementation()
{
	if (!CanBasic())
	{
		return;
	}
	WeaponAction->SetRepeat(true);
	if (WeaponAction->IsRunning())
	{
		WeaponAction->NetExecuteAciton();
	}
}

void UAutoWeapon::ServerBasicReleased_Implementation()
{
	WeaponAction->SetRepeat(false);
}

