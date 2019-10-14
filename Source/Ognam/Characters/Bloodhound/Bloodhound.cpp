// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloodhound.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BloodhoundClaws.h"
#include "BloodhoundPiercingThorns.h"
#include "BloodhoundEtchedStalker.h"
#include "BloodhoundWithhold.h"

ABloodhound::ABloodhound()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(61.6f);
	GetCapsuleComponent()->SetCapsuleRadius(23.8f);
	GetMesh()->SetRelativeScale3D(FVector(.7f));
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -63.f));

	CharacterName = FText::FromString("Bloodhound");
}

void ABloodhound::BeginPlay()
{
	Super::BeginPlay();

	Weapon = NewObject<UBloodhoundClaws>(this, TEXT("Weapon"));
	Mobility = NewObject<UBloodhoundEtchedStalker>(this, TEXT("Mobility"));
	Unique = NewObject<UBloodhoundPiercingThorns>(this, TEXT("Unique"));
	Utility = NewObject<UBloodhoundWithhold>(this, TEXT("Utility"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
	Utility->RegisterComponent();
}
