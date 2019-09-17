// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellClaretStrikeCharging.h"
#include "MaxwellClaretStrikeCharged.h"
#include "MaxwellAimDowned.h"
#include "Ognam/OgnamCharacter.h"
#include "UnrealNetwork.h"

UMaxwellClaretStrikeCharging::UMaxwellClaretStrikeCharging()
{
	StatusEffect |= EStatusEffect::Unarmed;
	Duration = 1.f;
}

bool UMaxwellClaretStrikeCharging::ShouldEnd()
{
	return !Target->GetModifier<UMaxwellAimDowned>() || Super::ShouldEnd();
}

void UMaxwellClaretStrikeCharging::EndModifier()
{
	if (!Target->GetModifier<UMaxwellAimDowned>() || !Target->HasAuthority())
	{
		return;
	}
	NewObject<UMaxwellClaretStrikeCharged>(Target)->RegisterComponent();
}
