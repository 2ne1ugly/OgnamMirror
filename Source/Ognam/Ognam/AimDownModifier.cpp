// Fill out your copyright notice in the Description page of Project Settings.


#include "AimDownModifier.h"
#include "ConstructorHelpers.h"

UAimDownModifier::UAimDownModifier()
{
	SetNetAddressable();
	MaxFocusTime = .4f;
}

void UAimDownModifier::StartAimDown()
{
	bAimDowned = true;
}

void UAimDownModifier::StopAimDown()
{
	bAimDowned = false;
}

void UAimDownModifier::TickModifier(float DeltaTime)
{
	Super::TickModifier(DeltaTime);
	FocusTime += bAimDowned ? DeltaTime : -DeltaTime;
	FocusTime = FMath::Clamp(FocusTime, 0.f, MaxFocusTime);
}

bool UAimDownModifier::IsSupportedForNetworking() const
{
	return true;
}
