// Fill out your copyright notice in the Description page of Project Settings.

#include "JeraSuppressiveImpact.h"
#include "JeraSuppressiveImpactBackSwing.h"
UJeraSuppressiveImpact::UJeraSuppressiveImpact()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 1.f;
}

void UJeraSuppressiveImpact::ActivateAbility()
{
	NewObject<UJeraSuppressiveImpactBackSwing>(Target)->RegisterComponent();
}
