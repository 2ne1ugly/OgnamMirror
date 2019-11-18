// Fill out your copyright notice in the Description page of Project Settings.

#include "Langdon.h"
#include "LangdonAutoRifle.h"
#include "LangdonSteamBracers.h"

ALangdon::ALangdon()
{

}

void ALangdon::BeginPlay()
{
	Super::BeginPlay();

	Weapon = NewObject<ULangdonAutoRifle>(this, TEXT("Weapon"));
	Mobility = NewObject<ULangdonSteamBracers>(this, TEXT("Mobility"));
//	Unique = NewObject<UBloodhoundHuntingHour>(this, TEXT("Unique"));
//	Special = NewObject <UBloodhoundImpactShotgun>(this, TEXT("Special"));
//	Utility = NewObject<UBloodhoundWithhold>(this, TEXT("Utility"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
//	Unique->RegisterComponent();
//	Special->RegisterComponent();
//	Utility->RegisterComponent();
}
