// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellSniperRifle.h"
#include "MaxwellAimDowned.h"
#include "Ognam/OgnamCharacter.h"
#include "MaxwellSniperRifleAction.h"

UMaxwellSniperRifle::UMaxwellSniperRifle()
{
	MaxAmmo = 8;
	Ammo = MaxAmmo;
	//RoundsPerSecond = 2.5f;
	ReloadTime = 3.5f;

	bBindSub = true;
	WeaponActionClass = UMaxwellSniperRifleAction::StaticClass();
}

void UMaxwellSniperRifle::SubPressed()
{
	if (Target->HasStatusEffect(EStatusEffect::Unarmed))
	{
		return;
	}
	ServerToggleAimDown();
}

void UMaxwellSniperRifle::ServerToggleAimDown_Implementation()
{
	if (Target->HasStatusEffect(EStatusEffect::Unarmed))
	{
		return;
	}
	UMaxwellAimDowned* Modifier = Target->GetModifier<UMaxwellAimDowned>();
	if (Modifier)
	{
		Modifier->Interrupt();
	}
	else
	{
		NewObject<UMaxwellAimDowned>(Target)->RegisterComponent();
	}
}
