// Copyright 2019 Ognam Studios. All Rights Reserved.
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
	float CurrentSeconds = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
	GetWorld()->GetTimerManager().SetTimer(DurationTimer, CurrentSeconds - ServerTimeStamp + Duration, false);
}

void UExpirableModifier::EndModifier()
{
}
