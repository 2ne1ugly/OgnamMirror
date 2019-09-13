// Fill out your copyright notice in the Description page of Project Settings.

#include "Maxwell.h"
#include "MaxwellSniperRifle.h"

AMaxwell::AMaxwell()
{

}

void AMaxwell::BeginPlay()
{
	Super::BeginPlay();
	Weapon = NewObject<UMaxwellSniperRifle>(this);
	//Mobility = NewObject<UHereiraSprint>(this);
	//Unique = NewObject<UHereiraLoadExplosiveShot>(this);
	Weapon->RegisterComponent();
	//Mobility->RegisterComponent();
	//Unique->RegisterComponent();
}
