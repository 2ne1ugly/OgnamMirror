// Fill out your copyright notice in the Description page of Project Settings.

#include "Maxwell.h"
#include "MaxwellSniperRifle.h"
#include "MaxwellShadowShift.h"
#include "MaxwellClaretStrike.h"
#include "Camera/CameraComponent.h"

AMaxwell::AMaxwell()
{
	AimDownedCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Aim Down"));
	AimDownedCamera->ComponentTags.Add(TEXT("ADS"));
	AimDownedCamera->SetupAttachment(RootComponent);
	AimDownedCamera->SetRelativeLocation(FVector(50.f, 0.f, 70.f));
	AimDownedCamera->bUsePawnControlRotation = true;
	//CameraComponent->bAllowConcurrentTick = true;
	AimDownedCamera->SetAbsolute(false, true);
	//CameraComponent->B
	AimDownedCamera->SetFieldOfView(30.f);

}

void AMaxwell::BeginPlay()
{
	Super::BeginPlay();
	Weapon = NewObject<UMaxwellSniperRifle>(this, TEXT("Weapon"));
	Mobility = NewObject<UMaxwellShadowShift>(this, TEXT("Mobility"));
	Unique = NewObject<UMaxwellClaretStrike>(this, TEXT("Unique"));

	Weapon->RegisterComponent();
	Mobility->RegisterComponent();
	Unique->RegisterComponent();
}
