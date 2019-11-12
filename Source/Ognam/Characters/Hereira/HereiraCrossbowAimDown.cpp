// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraCrossbowAimDown.h"
#include "ConstructorHelpers.h"
#include "Ognam/OgnamCharacter.h"
#include "Camera/CameraComponent.h"
#include "Curves/CurveFloat.h"

UHereiraCrossbowAimDown::UHereiraCrossbowAimDown()
{
	static ConstructorHelpers::FObjectFinder<UCurveFloat> FovCH(TEXT("CurveFloat'/Game/Curve/Hereira/HereiralAimDownFOV.HereiralAimDownFOV'"));
	FovCurve = FovCH.Object;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> SpeedCH(TEXT("CurveFloat'/Game/Curve/Hereira/HereiraAimDownSlow.HereiraAimDownSlow'"));
	SpeedCurve = SpeedCH.Object;

	MaxFocusTime = 0.15f;
}

void UHereiraCrossbowAimDown::TickModifier(float DeltaTime)
{
	Super::TickModifier(DeltaTime);

	Target->Camera->SetFieldOfView(FovCurve->GetFloatValue(FocusTime / MaxFocusTime));
	Target->Speed *= SpeedCurve->GetFloatValue(FocusTime / MaxFocusTime);
}
