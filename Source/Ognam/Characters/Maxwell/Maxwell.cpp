// Fill out your copyright notice in the Description page of Project Settings.

#include "Maxwell.h"
#include "MaxwellSniperRifle.h"
#include "MaxwellShadowShift.h"

AMaxwell::AMaxwell()
{

}

void AMaxwell::BeginPlay()
{
	Super::BeginPlay();
	Weapon = NewObject<UMaxwellSniperRifle>(this, TEXT("Weapon"));
	Mobility = NewObject<UMaxwellShadowShift>(this, TEXT("Mobility"));
	//Unique = NewObject<UHereiraLoadExplosiveShot>(this);

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	//Unique->RegisterComponent();
}
