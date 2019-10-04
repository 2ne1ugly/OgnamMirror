// Fill out your copyright notice in the Description page of Project Settings.

#include "ClipWeapon.h"
#include "OgnamCharacter.h"
#include "UnrealNetwork.h"
#include "TimerManager.h"

UClipWeapon::UClipWeapon()
{
	ReloadTime = 3.f;
}

void UClipWeapon::BeginPlay()
{
	Super::BeginPlay();

	ReloadPressHandle = Target->OnReloadPressed.AddUObject(this, &UClipWeapon::Reload);
}

void UClipWeapon::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Target->OnReloadPressed.Remove(ReloadPressHandle);
}

void UClipWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UClipWeapon, bReloading);
	DOREPLIFETIME_CONDITION(UClipWeapon, Ammo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UClipWeapon, MaxAmmo, COND_OwnerOnly);
}

bool UClipWeapon::IsReloading() const
{
	return bReloading;
}

int32 UClipWeapon::GetAmmo() const
{
	return Ammo;
}

int32 UClipWeapon::GetMaxAmmo() const
{
	return MaxAmmo;
}

void UClipWeapon::Reload()
{
	if (Ammo == MaxAmmo || bReloading)
	{
		return;
	}
	ServerReload();
}

void UClipWeapon::ServerReload_Implementation()
{
	if (Ammo == MaxAmmo || bReloading)
	{
		return;
	}
	bReloading = true;
	Target->GetWorldTimerManager().SetTimer(ReloadTimer, this, &UClipWeapon::EndReload, ReloadTime, false);
}

void UClipWeapon::EndReload()
{
	bReloading = false;
	Ammo = MaxAmmo;
}

void UClipWeapon::StatusEffectApplied(EStatusEffect StatusEffect)
{
	//Status effects that will cancel reload.
}

void UClipWeapon::ActionTaken(EActionNotifier ActionType)
{
	if (bReloading && ActionType == EActionNotifier::Focus)
	{
		bReloading = false;
		Target->GetWorldTimerManager().ClearTimer(ReloadTimer);
//			SetTimer(ReloadTimer, this, &UClipWeapon::EndReload, ReloadTime, false);
	}
}
