// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundImpactShotgun.h"
#include "BloodhoundImpactShotgunAction.h"

UBloodhoundImpactShotgun::UBloodhoundImpactShotgun()
{
	AbilityType = EAbilityType::Special;
	Cooldown = 1.f;
}

void UBloodhoundImpactShotgun::ActivateAbility()
{
	NewObject<UBloodhoundImpactShotgunAction>(GetOwner())->RegisterComponent();
}
