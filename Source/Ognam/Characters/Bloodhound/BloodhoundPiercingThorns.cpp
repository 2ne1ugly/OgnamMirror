// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundPiercingThorns.h"
#include "BloodhoundPiercingThornsAction.h"

UBloodhoundPiercingThorns::UBloodhoundPiercingThorns()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 1.f;
}

void UBloodhoundPiercingThorns::ActivateAbility()
{
	//Think about when used in mid air. should we block jumping? what about when used while droping?
	NewObject<UBloodhoundPiercingThornsAction>(this)->RegisterComponent();
}
