// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "MaxwellVault.h"
#include "Ognam/OgnamCharacter.h"
#include "MaxwellVaultModifier.h"
#include "Engine/World.h"
#include "TimerManager.h"

UMaxwellVault::UMaxwellVault()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 10.f;
}

void UMaxwellVault::ActivateAbility()
{
	Target->LaunchCharacter(FVector::UpVector * 2700.f, false, true);
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UMaxwellVault::ApplyModifier);
}

void UMaxwellVault::ApplyModifier()
{
	NewObject<UMaxwellVaultModifier>(Target)->RegisterComponent();
}
