// Fill out your copyright notice in the Description page of Project Settings.

#include "LangdonAutoRifleAimDown.h"
#include "ConstructorHelpers.h"
#include "Curves/CurveFloat.h"
#include "Ognam/OgnamCharacter.h"
#include "Camera/CameraComponent.h"

ULangdonAutoRifleAimDown::ULangdonAutoRifleAimDown()
{
	static ConstructorHelpers::FObjectFinder<UCurveFloat> FovCH(TEXT("CurveFloat'/Game/Curve/Langdon/LangdonAimDownFOV.LangdonAimDownFOV'"));
	FovCurve = FovCH.Object;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> SpeedCH(TEXT("CurveFloat'/Game/Curve/Langdon/LangdonAimDownSlow.LangdonAimDownSlow'"));
	SpeedCurve = SpeedCH.Object;

	MaxFocusTime = 0.15f;
}

void ULangdonAutoRifleAimDown::TickModifier(float DeltaTime)
{
	Super::TickModifier(DeltaTime);

	Target->Camera->SetFieldOfView(FovCurve->GetFloatValue(FocusTime / MaxFocusTime));
	Target->Speed *= SpeedCurve->GetFloatValue(FocusTime / MaxFocusTime);
}
