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
	UnacceptedStatusEffects = EStatusEffect::Unarmed;

	bReloadOnNoAmmo = true;
}

void USemiAutoClipWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(USemiAutoClipWeapon, bCanFire, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(USemiAutoClipWeapon, bCharging, COND_OwnerOnly);
}

void USemiAutoClipWeapon::BasicPressed()
{
	if (bReloading ||
		Ammo <= 0 ||
		!bCanFire ||
		Target->HasStatusEffect(UnacceptedStatusEffects) ||
		bCharging)
	{
		if (Ammo == 0)
		{
			Reload();
		}
		return;
	}
	ServerBasicPressed();
}

void USemiAutoClipWeapon::BasicReleased()
{
	if (!bFireOnRelease ||
		!bCharging ||
		bReloading ||
		Ammo <= 0 ||
		!bCanFire ||
		Target->HasStatusEffect(UnacceptedStatusEffects))
	{
		return;
	}
	ServerBasicReleased();
}

void USemiAutoClipWeapon::ServerBasicPressed_Implementation()
{
	if (bReloading ||
		Ammo <= 0 ||
		!bCanFire ||
		Target->HasStatusEffect(UnacceptedStatusEffects) ||
		bCharging)
	{
		return;
	}

	if (bFireOnRelease)
	{
		bCharging = true;
		return;
	}

	PreFireBullet();
	FireBullet();
	PostFireBullet();
}

void USemiAutoClipWeapon::ServerBasicReleased_Implementation()
{
	if (!bFireOnRelease ||
		!bCharging ||
		bReloading ||
		Ammo <= 0 ||
		!bCanFire ||
		Target->HasStatusEffect(UnacceptedStatusEffects))
	{
		return;
	}

	PreFireBullet();
	FireBullet();
	PostFireBullet();
}

void USemiAutoClipWeapon::PreFireBullet()
{
	Ammo--;
	bCharging = false;
	bCanFire = false;
	Target->GetWorldTimerManager().SetTimer(PostDelay, this, &USemiAutoClipWeapon::EndPostDelay, 1.f / RoundsPerSecond, false);
}

void USemiAutoClipWeapon::FireBullet()
{
}

void USemiAutoClipWeapon::PostFireBullet()
{
	if (Ammo == 0 && bReloadOnNoAmmo)
	{
		ServerReload_Implementation();
	}
}

void USemiAutoClipWeapon::EndPostDelay()
{
	bCanFire = true;
}
