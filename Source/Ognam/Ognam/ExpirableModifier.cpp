// Fill out your copyright notice in the Description page of Project Settings.

#include "ExpirableModifier.h"
#include "Engine/World.h"
#include "TimerManager.h"

bool UExpirableModifier::ShouldEnd()
{
	return !GetWorld()->GetTimerManager().IsTimerActive(Duration);
}

void UExpirableModifier::TickModifier(float DeltaTime)
{
}

void UExpirableModifier::BeginModifier()
{
	GetWorld()->GetTimerManager().SetTimer(Duration, 3.f, false);
}

void UExpirableModifier::EndModifier()
{
}
