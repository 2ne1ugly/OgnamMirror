// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelDisruptiveBurst.h"
#include "HazelBursting.h"
#include "Engine/World.h"
UHazelDisruptiveBurst::UHazelDisruptiveBurst()
{
	AbilityType = EAbilityType::Special;
	Cooldown = 10.f;
}

void UHazelDisruptiveBurst::ActivateAbility()
{
	NewObject<UHazelBursting>(Target)->RegisterComponent();
}
