// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellRecovering.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Ognam/OgnamCharacter.h"
#include "Kismet/GameplayStatics.h"

UMaxwellRecovering::UMaxwellRecovering()
{
	Duration = 30.f;
	HealthPenalty = 60.f;
	TickPeriod = 1.f;
}

void UMaxwellRecovering::BeginModifier()
{
	Super::BeginModifier();
	
	UGameplayStatics::TakeDamage();
	Target->Health -= HealthPenalty;
	GetWorld()->GetTimerManager().SetTimer(HealTickTimer, this, &UMaxwellRecovering::HealTick, true);
}

void UMaxwellRecovering::HealTick()
{
	Target->Health += HealthPenalty / Duration * TickPeriod;
}
