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
}

void USemiAutoClipWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(USemiAutoClipWeapon, bCanFire, COND_OwnerOnly);
}

void USemiAutoClipWeapon::BasicPressed()
{
	if (bReloading || Ammo <= 0 || !bCanFire || Target->HasStatusEffect(UnacceptedStatusEffects))
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
	if (bReloading || Ammo <= 0 || !bCanFire || Target->HasStatusEffect(UnacceptedStatusEffects))
	{
		return;
	}
	Ammo--;
	FireBullet();
	bCanFire = false;
	Target->GetWorldTimerManager().SetTimer(PostDelay, this, &USemiAutoClipWeapon::EndPostDelay, 1.f / RoundsPerSecond, false);
	if (Ammo <= 0)
	{
		ServerReload_Implementation();
	}
}

void USemiAutoClipWeapon::FireBullet()
{
}

void USemiAutoClipWeapon::EndPostDelay()
{
	bCanFire = true;
}
