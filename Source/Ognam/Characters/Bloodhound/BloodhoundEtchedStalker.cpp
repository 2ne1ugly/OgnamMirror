// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundEtchedStalker.h"
#include "BloodhoundEtchedStalkerAction.h"

UBloodhoundEtchedStalker::UBloodhoundEtchedStalker()
{
	AbilityType = EAbilityType::Mobility;
	Cooldown = 4.f;
}

void UBloodhoundEtchedStalker::ActivateAbility()
{
	NewObject<UBloodhoundEtchedStalkerAction>(this)->RegisterComponent();
}
