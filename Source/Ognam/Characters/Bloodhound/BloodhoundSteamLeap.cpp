// Fill out your copyright notice in the Description page of Project Settings.

#include "BloodhoundSteamLeap.h"
#include "BloodhoundSteamLeapAction.h"
#include "ConstructorHelpers.h"

UBloodhoundSteamLeap::UBloodhoundSteamLeap()
{
	AbilityType = EAbilityType::Mobility;
	Cooldown = 7.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Bloodhound/steam_leap.steam_leap'"));
	Icon = IconTexture.Object;
}

void UBloodhoundSteamLeap::ActivateAbility()
{
	NewObject<UBloodhoundSteamLeapAction>(GetOwner())->RegisterComponent();
}
