// Fill out your copyright notice in the Description page of Project Settings.

#include "Maxwell.h"
#include "MaxwellSniperRifle.h"
#include "MaxwellShadowShift.h"
#include "MaxwellClaretStrike.h"
//#include "Camera/CameraComponent.h"

AMaxwell::AMaxwell()
{
	CharacterName = FText::FromString("Maxwell");
}

void AMaxwell::BeginPlay()
{
	Super::BeginPlay();
	Weapon = NewObject<UMaxwellSniperRifle>(this, TEXT("Weapon"));
	Mobility = NewObject<UMaxwellShadowShift>(this, TEXT("Mobility"));
	Unique = NewObject<UMaxwellClaretStrike>(this, TEXT("Unique"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
}
