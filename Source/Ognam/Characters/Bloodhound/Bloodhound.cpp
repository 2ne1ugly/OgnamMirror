// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloodhound.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BloodhoundClaws.h"
#include "BloodhoundWithhold.h"
#include "BloodhoundHuntingHour.h"
#include "BloodhoundSteamLeap.h"
#include "BloodhoundImpactShotgun.h"
#include "ConstructorHelpers.h"

const FVector ABloodhound::MetalPositions[3] = {
	FVector(35.f, 0.f, 50.f),
	FVector(-35.f, 5.f, 100.f),
	FVector(-15.f, -30.f, 150.f)
};

const FVector ABloodhound::MetalScales[3] = {
	FVector(.1f, .25f, .25f),
	FVector(.1f, .25f, .25f),
	FVector(.25f, .1f, .25f)
};

ABloodhound::ABloodhound()
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(61.6f);
	GetCapsuleComponent()->SetCapsuleRadius(23.8f);
	GetMesh()->SetRelativeScale3D(FVector(.7f));
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -63.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MetalMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	for (int i = 0; i < 3; i++)
	{
		Metals[i] = CreateDefaultSubobject<UStaticMeshComponent>(*(FString::Printf(TEXT("Metal%d"), i)));
		Metals[i]->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Metals[i]->SetStaticMesh(MetalMesh.Object);
		Metals[i]->SetRelativeLocation(MetalPositions[i]);
		Metals[i]->SetRelativeScale3D(MetalScales[i]);
		Metals[i]->ComponentTags.Add(TEXT("Metal"));
		Metals[i]->SetupAttachment(GetMesh());
	}

	CharacterName = FText::FromString("Bloodhound");
}

void ABloodhound::BeginPlay()
{
	Super::BeginPlay();

	Weapon = NewObject<UBloodhoundClaws>(this, TEXT("Weapon"));
	Mobility = NewObject<UBloodhoundSteamLeap>(this, TEXT("Mobility"));
	Unique = NewObject<UBloodhoundHuntingHour>(this, TEXT("Unique"));
	Special = NewObject <UBloodhoundImpactShotgun>(this, TEXT("Special"));
	Utility = NewObject<UBloodhoundWithhold>(this, TEXT("Utility"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
	Special->RegisterComponent();
	Utility->RegisterComponent();
}
