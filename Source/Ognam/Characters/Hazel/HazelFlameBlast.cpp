// Fill out your copyright notice in the Description page of Project Settings.

#include "HazelFlameBlast.h"
#include "HazelFlameBlastAction.h"

UHazelFlameBlast::UHazelFlameBlast()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 6.f;
}

void UHazelFlameBlast::ActivateAbility()
{
	NewObject<UHazelFlameBlastAction>(Target)->RegisterComponent();
}
