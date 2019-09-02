// Fill out your copyright notice in the Description page of Project Settings.

#include "HereiraCanFastReload.h"
#include "Engine/World.h"

bool UHereiraCanFastReload::ShouldEnd()
{
	return !GetWorld()->GetTimerManager().IsTimerActive(Duration) || bUsed;
}

void UHereiraCanFastReload::BeginModifier()
{
	GetWorld()->GetTimerManager().SetTimer(Duration, 3.f, false);
}

bool UHereiraCanFastReload::Use()
{
	bool bResult = !bUsed;
	bUsed = true;
	return bResult;
}
