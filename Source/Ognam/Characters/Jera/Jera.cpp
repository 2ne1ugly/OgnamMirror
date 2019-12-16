// Fill out your copyright notice in the Description page of Project Settings.


#include "Jera.h"
#include "JeraCrystalArms.h"
#include "JeraRadiantDive.h"
#include "JeraSuppressiveImpact.h"
#include "Ognam/OgnamMacro.h"
#include "Components/SkeletalMeshComponent.h"

AJera::AJera()
{
	GetMesh()->SetRelativeScale3D(FVector(1.1f));
	BaseMaxHealth = 250.f;

	CharacterName = FText::FromString("Jera");

	static ConstructorHelpers::FObjectFinder<USoundCue> WalkingCue(TEXT("SoundCue'/Game/Sounds/Jera/Jera_walk_Cue.Jera_walk_Cue'"));
	WalkingSoundCue = WalkingCue.Object;
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
