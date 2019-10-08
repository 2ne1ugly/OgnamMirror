// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoClipWeapon.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamCharacter.h"
#include "TimerManager.h"

UAutoClipWeapon::UAutoClipWeapon()
{
	RoundsPerSecond = 10.f;
	MaxAmmo = 30.f;
	Ammo = MaxAmmo;
	UnacceptedStatusEffects = EStatusEffect::Unarmed;

	bReloadOnNoAmmo = true;
}

void UAutoClipWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UAutoClipWeapon, bFiring, COND_OwnerOnly);
}

void UAutoClipWeapon::BasicPressed()
{
	if (bReloading ||
		Ammo <= 0 ||
		Target->HasStatusEffect(UnacceptedStatusEffects))
	{
		if (Ammo == 0)
		{
			Reload();
		}
		return;
	}
	ServerBasicPressed();
}

void UAutoClipWeapon::BasicReleased()
{
	ServerBasicReleased();
}

void UAutoClipWeapon::ServerBasicPressed_Implementation()
{
	if (bReloading ||
		Ammo <= 0 ||
		bWantsToFire ||
		Target->HasStatusEffect(UnacceptedStatusEffects))
	{
		return;
	}
	bWantsToFire = true;
	if (!bFiring)
	{
		StartFireBullet();
	}
}

void UAutoClipWeapon::ServerBasicReleased_Implementation()
{
	if (!bWantsToFire)
	{
		return;
	}
	bWantsToFire = false;
}

void UAutoClipWeapon::StartFireBullet()
{
	bFiring = true;
	PreFireBullet();
	FireBullet();
	PostFireBullet();
}

void UAutoClipWeapon::RepeatFireBullet()
{
	if (Ammo <= 0 ||
		bReloading ||
		!bWantsToFire ||
		Target->HasStatusEffect(UnacceptedStatusEffects))
	{
		EndFireBullet();
		return;
	}
	PreFireBullet();
	FireBullet();
	PostFireBullet();
}

void UAutoClipWeapon::EndFireBullet()
{
	bFiring = false;
	if (bReloadOnNoAmmo && Ammo == 0)
	{
		ServerReload_Implementation();
	}
}

void UAutoClipWeapon::PreFireBullet()
{
	if (!bInfiniteAmmo)
	{
		Ammo--;
	}
}

void UAutoClipWeapon::FireBullet()
{
}

void UAutoClipWeapon::PostFireBullet()
{
	Target->GetWorldTimerManager().SetTimer(PostDelay, this, &UAutoClipWeapon::RepeatFireBullet, 1.f / RoundsPerSecond, false);
}
