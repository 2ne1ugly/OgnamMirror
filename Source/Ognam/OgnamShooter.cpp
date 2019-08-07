// Fill out your copyright notice in the Description page of Project Settings.

#include "OgnamShooter.h"
#include "UnrealNetwork.h"

int32 AOgnamShooter::GetAmmo() const
{
	return Ammo	;
}

int32 AOgnamShooter::GetMaxAmmo() const
{
	return MaxAmmo;
}

AOgnamShooter::AOgnamShooter()
{
	Ammo = 0;
	MaxAmmo = 12;
}

void AOgnamShooter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamShooter, Ammo);
	DOREPLIFETIME(AOgnamShooter, MaxAmmo);
}
