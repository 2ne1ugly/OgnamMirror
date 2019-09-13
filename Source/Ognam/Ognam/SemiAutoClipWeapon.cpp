// Fill out your copyright notice in the Description page of Project Settings.

#include "SemiAutoClipWeapon.h"
#include "UnrealNetwork.h"
#include "OgnamCharacter.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "GameFramework/GameState.h"

USemiAutoClipWeapon::USemiAutoClipWeapon()
{
	RoundsPerSecond = 2;
	bCanFire = true;
}

void USemiAutoClipWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(USemiAutoClipWeapon, bCanFire, COND_OwnerOnly);
}

void USemiAutoClipWeapon::BasicPressed()
{
	if (bReloading || Ammo <= 0 || !bCanFire)
	{
		if (Ammo == 0)
		{
			Reload();
		}
		return;
	}
	ServerBasicPressed();
}

void USemiAutoClipWeapon::ServerBasicPressed_Implementation()
{
	if (bReloading || Ammo <= 0 || !bCanFire)
	{
		return;
	}
	Ammo--;
	FireBullet();
	bCanFire = false;
	Target->GetWorldTimerManager().SetTimer(PostDelay, this, &USemiAutoClipWeapon::EndPostDelay, 1.f / RoundsPerSecond, false);
}

void USemiAutoClipWeapon::FireBullet()
{
}

void USemiAutoClipWeapon::EndPostDelay()
{
	bCanFire = true;
}
