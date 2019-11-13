// Fill out your copyright notice in the Description page of Project Settings.


#include "Jera.h"
#include "JeraCrystalArms.h"
#include "JeraRadiantDive.h"
#include "JeraSuppressiveImpact.h"
#include "Ognam/OgnamMacro.h"

AJera::AJera()
{
	RootComponent->SetRelativeScale3D(FVector(1.1f));
	BaseMaxHealth = 300.f;
	MaxHealth = BaseMaxHealth;
	Health = MaxHealth;

	CharacterName = FText::FromString("Jera");
}

void AJera::BeginPlay()
{
	Super::BeginPlay();

	Weapon = NewObject<UJeraCrystalArms>(this, TEXT("Weapon"));
	Mobility = NewObject<UJeraRadiantDive>(this, TEXT("Mobility"));
	Unique = NewObject<UJeraSuppressiveImpact>(this, TEXT("Unique"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
}
