// Fill out your copyright notice in the Description page of Project Settings.


#include "Asha.h"
#include "Ognam/OgnamMacro.h"
#include "AshaThrowingDaggers.h"
#include "AshaWhirlingBlades.h"
#include "AshaFanofKnives.h"
#include "Components/SkeletalMeshComponent.h"

AAsha::AAsha()
{
	GetMesh()->SetRelativeScale3D(FVector(0.95f));
	BaseMaxHealth = 200.f;

	CharacterName = FText::FromString("Asha");
}

void AAsha::BeginPlay()
{
	Super::BeginPlay();

	Weapon = NewObject<UAshaThrowingDaggers>(this, TEXT("Weapon"));
	Mobility = NewObject<UAshaWhirlingBlades>(this, TEXT("Mobility"));
	Unique = NewObject<UAshaFanofKnives>(this, TEXT("Unique"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
}
