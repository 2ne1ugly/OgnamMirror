// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundClaws.h"
#include "BloodhoundClawsAction.h"
#include "BloodhoundHuntingHour.h"
#include "Ognam/OgnamCharacter.h"

UBloodhoundClaws::UBloodhoundClaws()
{
	WeaponActionClass = UBloodhoundClawsAction::StaticClass();
	bInfiniteAmmo = true;
}

void UBloodhoundClaws::ServerBasicPressed_Implementation()
{
	UBloodhoundHuntingHour* Hour = Target->GetModifier<UBloodhoundHuntingHour>();
	if (!Hour)
	{
		Super::ServerBasicPressed_Implementation();
	}
	else if (CanBasic())
	{
		Hour->Consume();
	}
}

