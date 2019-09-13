// Fill out your copyright notice in the Description page of Project Settings.

#include "HereiraExplosiveShotReady.h"
#include "HereiraLoadExplosiveShot.h"
#include "UnrealNetwork.h"

bool UHereiraExplosiveShotReady::ShouldEnd()
{
	return bUsed;
}

void UHereiraExplosiveShotReady::SetAbility(UHereiraLoadExplosiveShot* LoadShot)
{
	Ability = LoadShot;
}

void UHereiraExplosiveShotReady::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHereiraExplosiveShotReady, bUsed);
}

bool UHereiraExplosiveShotReady::Use()
{
	bool bResult = !bUsed;
	bUsed = true;
	Ability->FiredExplosiveShot();
	return bResult;
}
