// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "OgnamCharacter.h"
#include "OgnamMacro.h"
#include "WeaponActionModifier.h"
#include "UnrealNetwork.h"
#include "TimerManager.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UWeapon::UWeapon()
{
	SetNetAddressable();
	SetIsReplicated(true);
	BasicBlockingEffects |= EStatusEffect::Unarmed;
	ReloadTime = 3.f;
	bReloadOnNoAmmo = true;
}

bool UWeapon::IsSupportedForNetworking() const
{
	return true;
}

void UWeapon::ExecuteWeaponActionNotify()
{
	if (!bInfiniteAmmo && GetOwner()->HasAuthority())
	{
		Ammo--;
	}
}

void UWeapon::FinishWeaponActionNotify()
{
	if (!bInfiniteAmmo && bReloadOnNoAmmo && Ammo <= 0 && GetOwner()->HasAuthority())
	{
		ServerReloadPressed_Implementation();
	}
}

bool UWeapon::IsReloading() const
{
	return bReloading;
}

int32 UWeapon::GetAmmo() const
{
	return Ammo;
}

int32 UWeapon::GetMaxAmmo() const
{
	return MaxAmmo;
}

bool UWeapon::IsInfinteAmmo() const
{
	return bInfiniteAmmo;
}

void UWeapon::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<AOgnamCharacter>(GetOwner());

	BasicPressHandle = Target->OnBasicPressed.AddUObject(this, &UWeapon::BasicPressed);
	BasicReleaseHandle = Target->OnBasicReleased.AddUObject(this, &UWeapon::BasicReleased);
	if (bBindSub)
	{
		SubPressHandle = Target->OnSubPressed.AddUObject(this, &UWeapon::SubPressed);
		SubReleaseHandle = Target->OnSubReleased.AddUObject(this, &UWeapon::SubReleased);
	}

	if (!WeaponActionClass)
	{
		O_LOG_F(TEXT("No Weapon action Class"));
		return;
	}
	WeaponAction = NewObject<UWeaponActionModifier>(GetOwner(), WeaponActionClass, TEXT("Weapon Action"));
	WeaponAction->RegisterComponent();

	if (!bInfiniteAmmo)
	{
		ReloadPressHandle = Target->OnReloadPressed.AddUObject(this, &UWeapon::ReloadPressed);

	}
}

void UWeapon::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Target->OnBasicPressed.Remove(BasicPressHandle);
	Target->OnBasicReleased.Remove(BasicReleaseHandle);
	if (SubPressHandle.IsValid())
	{
		Target->OnSubPressed.Remove(SubPressHandle);
		Target->OnSubReleased.Remove(SubReleaseHandle);
	}

	if (ReloadPressHandle.IsValid())
	{
		Target->OnReloadPressed.Remove(ReloadPressHandle);
	}
}

void UWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeapon, bReloading);
	DOREPLIFETIME_CONDITION(UWeapon, Ammo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UWeapon, MaxAmmo, COND_OwnerOnly);
}

void UWeapon::BasicPressed()
{
	//This part is really dependent on each weapon.
}

void UWeapon::BasicReleased()
{
	//This part is really dependent on each weapon.
}

void UWeapon::SubPressed()
{
}

void UWeapon::SubReleased()
{
}

void UWeapon::ReloadPressed()
{
	//Consider moving reload as action.
	if (bInfiniteAmmo)
	{
		O_LOG_E(TEXT("bInfiniteAmmo is on when trying to reload"));
	}

	if (Ammo == MaxAmmo || bReloading)
	{
		return;
	}
	ServerReloadPressed();
}

void UWeapon::ServerReloadPressed_Implementation()
{
	if (bInfiniteAmmo)
	{
		O_LOG(TEXT("Reload is requested when InfiniteAmmo"));
		return;
	}

	if (Ammo == MaxAmmo || bReloading)
	{
		return;
	}
	bReloading = true;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &UWeapon::EndReload, ReloadTime, false);
}

void UWeapon::EndReload()
{
	bReloading = false;
	Ammo = MaxAmmo;
}

bool UWeapon::CanBasic()
{
	return !Target->HasStatusEffect(BasicBlockingEffects) &&
		!bReloading &&
		(bInfiniteAmmo || Ammo > 0);
}
