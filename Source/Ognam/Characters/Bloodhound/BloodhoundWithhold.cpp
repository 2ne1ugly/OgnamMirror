// Fill out your copyright notice in the Description page of Project Settings.

#include "BloodhoundWithhold.h"
#include "BloodhoundWithholdAction.h"

UBloodhoundWithhold::UBloodhoundWithhold()
{
	AbilityType = EAbilityType::Utility;

	Cooldown = 9.f;
}

void UBloodhoundWithhold::ActivateAbility()
{
	NewObject<UBloodhoundWithholdAction>(Target)->RegisterComponent();
}
