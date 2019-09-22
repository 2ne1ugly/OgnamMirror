// Fill out your copyright notice in the Description page of Project Settings.


#include "Jera.h"
#include "JeraRadiantDive.h"

AJera::AJera()
{
	RootComponent->SetRelativeScale3D(FVector(1.1f, 1.1f, 1.1f));
}

void AJera::BeginPlay()
{
	Super::BeginPlay();

	//Weapon = NewObject<UHereiraCrossbow>(this, TEXT("Sprint"));
	Mobility = NewObject<UJeraRadiantDive>(this, TEXT("Mobility"));
	//Unique = NewObject<UHereiraThrowMolotov>(this, TEXT("Unique"));

	//Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	//Unique->RegisterComponent();
}
