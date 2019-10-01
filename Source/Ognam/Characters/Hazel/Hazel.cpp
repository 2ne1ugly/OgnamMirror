// Fill out your copyright notice in the Description page of Project Settings.


#include "Hazel.h"
#include "HazelPyromancy.h"
#include "HazelBlazingWill.h"
#include "HazelFlameBlast.h"

AHazel::AHazel()
{
}

void AHazel::BeginPlay()
{
	Super::BeginPlay();

	Weapon = NewObject<UHazelPyromancy>(this, TEXT("Weapon"));
	Mobility = NewObject<UHazelBlazingWill>(this, TEXT("Mobility"));
	Unique = NewObject<UHazelFlameBlast>(this, TEXT("Unique"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
}
