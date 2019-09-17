// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellClaretStrikeCharged.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamCharacter.h"
#include "MaxwellAimDowned.h"

UMaxwellClaretStrikeCharged::UMaxwellClaretStrikeCharged()
{
}

bool UMaxwellClaretStrikeCharged::ShouldEnd()
{
	return bUsed || !Target->GetModifier<UMaxwellAimDowned>();
}

void UMaxwellClaretStrikeCharged::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMaxwellClaretStrikeCharged, bUsed)
}

bool UMaxwellClaretStrikeCharged::Use()
{
	bool bResult = !bUsed;
	bUsed = true;
	return bResult;
}
