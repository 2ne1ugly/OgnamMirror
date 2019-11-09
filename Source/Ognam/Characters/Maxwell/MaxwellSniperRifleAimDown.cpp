// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellSniperRifleAimDown.h"
#include "Curves/CurveFloat.h"
#include "Camera/CameraComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "ConstructorHelpers.h"
#include "Ognam/OgnamMacro.h"

UMaxwellSniperRifleAimDown::UMaxwellSniperRifleAimDown()
{
	static ConstructorHelpers::FObjectFinder<UCurveFloat> FovCH(TEXT("CurveFloat'/Game/Curve/Maxwell/MaxwellAimDownFov.MaxwellAimDownFOV'"));
	FovCurve = FovCH.Object;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> SpeedCH(TEXT("CurveFloat'/Game/Curve/Maxwell/MaxwellAimDownSlow.MaxwellAimDownSlow'"));
	SpeedCurve = SpeedCH.Object;

	MaxFocusTime = 0.15f;
}

void UMaxwellSniperRifleAimDown::TickModifier(float DeltaTime)
{
	Super::TickModifier(DeltaTime);

	Target->Camera->SetFieldOfView(FovCurve->GetFloatValue(FocusTime / MaxFocusTime));
	Target->Speed *= SpeedCurve->GetFloatValue(FocusTime / MaxFocusTime);
}
