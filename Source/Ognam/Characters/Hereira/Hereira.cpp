// Fill out your copyright notice in the Description page of Project Settings.

#include "Hereira.h"
#include "HereiraSprint.h"
#include "HereiraCrossbow.h"
#include "HereiraThrowMolotov.h"
#include "Sound/SoundCue.h"

AHereira::AHereira()
{
	CharacterName = FText::FromString(TEXT("Hereira"));
}

void AHereira::BeginPlay()
{
	Super::BeginPlay();
	Weapon = NewObject<UHereiraCrossbow>(this, TEXT("Weapon"));
	Mobility = NewObject<UHereiraSprint>(this, TEXT("Mobility"));
	Unique = NewObject<UHereiraThrowMolotov>(this, TEXT("Unique"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
}
