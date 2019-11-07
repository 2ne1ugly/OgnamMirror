// Fill out your copyright notice in the Description page of Project Settings.

#include "BloodhoundWithhold.h"
#include "BloodhoundWithholdAction.h"
#include "ConstructorHelpers.h"

UBloodhoundWithhold::UBloodhoundWithhold()
{
	AbilityType = EAbilityType::Utility;

	Cooldown = 9.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Bloodhound/detonation_switch.detonation_switch'"));
	Icon = IconTexture.Object;
}

void UBloodhoundWithhold::ActivateAbility()
{
	NewObject<UBloodhoundWithholdAction>(Target)->RegisterComponent();
}
