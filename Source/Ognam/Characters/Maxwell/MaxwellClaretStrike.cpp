// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellClaretStrike.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamCharacter.h"
#include "MaxwellAimDowned.h"
#include "MaxwellClaretStrikeCharged.h"
#include "MaxwellClaretStrikeCharging.h"

UMaxwellClaretStrike::UMaxwellClaretStrike()
{
	AbilityType = EAbilityType::Unique;
}

void UMaxwellClaretStrike::OnButtonPressed()
{
	if (!Target->GetModifier<UMaxwellAimDowned>() ||
		Target->GetModifier<UMaxwellClaretStrikeCharged>() ||
		Target->GetModifier<UMaxwellClaretStrikeCharging>() ||
		Target->HasStatusEffect(EStatusEffect::Silenced))
	{
		return;
	}
	ServerChargeClaretStrike();
}

void UMaxwellClaretStrike::ServerChargeClaretStrike_Implementation()
{
	if (!Target->GetModifier<UMaxwellAimDowned>() ||
		Target->GetModifier<UMaxwellClaretStrikeCharged>() ||
		Target->GetModifier<UMaxwellClaretStrikeCharging>() ||
		Target->HasStatusEffect(EStatusEffect::Silenced))
	{
		return;
	}
	NewObject<UMaxwellClaretStrikeCharging>(Target)->RegisterComponent();
}
