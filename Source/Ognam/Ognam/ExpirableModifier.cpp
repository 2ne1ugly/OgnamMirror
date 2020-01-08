// Fill out your copyright notice in the Description page of Project Settings.

#include "ExpirableModifier.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/GameStateBase.h"

UExpirableModifier::UExpirableModifier()
{
	Duration = 3.f;
}

bool UExpirableModifier::ShouldEnd()
{
	return !GetWorld()->GetTimerManager().IsTimerActive(DurationTimer);
}

void UExpirableModifier::TickModifier(float DeltaTime)
{
}

void UExpirableModifier::BeginModifier()
{	
	GetWorld()->GetTimerManager().SetTimer(DurationTimer, Duration, false);
}

void UExpirableModifier::EndModifier()
{
}
