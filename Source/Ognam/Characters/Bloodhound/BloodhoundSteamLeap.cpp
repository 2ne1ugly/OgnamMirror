// Fill out your copyright notice in the Description page of Project Settings.

#include "BloodhoundSteamLeap.h"
#include "BloodhoundSteamLeapAction.h"

UBloodhoundSteamLeap::UBloodhoundSteamLeap()
{
	AbilityType = EAbilityType::Mobility;
	Cooldown = 7.f;
}

void UBloodhoundSteamLeap::ActivateAbility()
{
	NewObject<UBloodhoundSteamLeapAction>(GetOwner())->RegisterComponent();
}
