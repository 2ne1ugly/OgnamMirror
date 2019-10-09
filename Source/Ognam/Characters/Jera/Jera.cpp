// Fill out your copyright notice in the Description page of Project Settings.


#include "Jera.h"
#include "JeraCrystalArms.h"
#include "JeraRadiantDive.h"
#include "JeraSuppressiveImpact.h"
#include "Ognam/OgnamMacro.h"

AJera::AJera()
{
	RootComponent->SetRelativeScale3D(FVector(1.1f));
	MaxHealth = 300.f;
}

void AJera::BeginPlay()
{
	Super::BeginPlay();

	Weapon = NewObject<UJeraCrystalArms>(this, TEXT("Weapon"));
	Mobility = NewObject<UJeraRadiantDive>(this, TEXT("Mobility"));
	Unique = NewObject<UJeraSuppressiveImpact>(this, TEXT("Unique"));

	O_LOG(TEXT("TEXT"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
}
