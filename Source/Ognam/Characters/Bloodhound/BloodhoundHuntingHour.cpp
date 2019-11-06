// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundHuntingHour.h"
#include "BloodhoundHuntingHourAction.h"

UBloodhoundHuntingHour::UBloodhoundHuntingHour()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 7.f;
}

void UBloodhoundHuntingHour::ActivateAbility()
{
	NewObject<UBloodhoundHuntingHourAction>(GetOwner())->RegisterComponent();
}
