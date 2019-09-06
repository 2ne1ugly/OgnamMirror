// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraSprint.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"

bool UHereiraSprint::ShouldEnd()
{
	return bInterrupted || !GetWorld()->GetTimerManager().IsTimerActive(Duration);
}

void UHereiraSprint::TickModifier(float DeltaTime)
{
	Target->Speed += Target->BaseSpeed * .5f;
}

void UHereiraSprint::Interrupt()
{
	bInterrupted = true;
}

void UHereiraSprint::BeginModifier()
{
	GetWorld()->GetTimerManager().SetTimer(Duration, 3.f, false);
}

void UHereiraSprint::EndModifier()
{
}
