// Fill out your copyright notice in the Description page of Project Settings.

#include "HazelPyromancyAimDown.h"
#include "ConstructorHelpers.h"
#include "Ognam/OgnamCharacter.h"
#include "Camera/CameraComponent.h"
#include "Curves/CurveFloat.h"

UHazelPyromancyAimDown::UHazelPyromancyAimDown()
{
	static ConstructorHelpers::FObjectFinder<UCurveFloat> FovCH(TEXT("CurveFloat'/Game/Curve/Hazel/HazelAimDownFOV.HazelAimDownFOV'"));
	FovCurve = FovCH.Object;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> SpeedCH(TEXT("CurveFloat'/Game/Curve/Hazel/HazelAimDownSlow.HazelAimDownSlow'"));
	SpeedCurve = SpeedCH.Object;

	MaxFocusTime = 0.15f;
}

void UHazelPyromancyAimDown::TickModifier(float DeltaTime)
{
	Super::TickModifier(DeltaTime);

	Target->Camera->SetFieldOfView(FovCurve->GetFloatValue(FocusTime / MaxFocusTime));
	Target->Speed *= SpeedCurve->GetFloatValue(FocusTime / MaxFocusTime);
}
