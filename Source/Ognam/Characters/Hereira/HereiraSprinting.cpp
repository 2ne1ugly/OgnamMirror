// Fill out your copyright notice in the Description page of Project Settings.

#include "HereiraSprinting.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"

UHereiraSprinting::UHereiraSprinting()
{
	StatusEffect |= EStatusEffect::Unarmed | EStatusEffect::Silenced;
}

void UHereiraSprinting::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UHereiraSprinting, Ability, COND_InitialOnly);
	DOREPLIFETIME(UHereiraSprinting, bInterrupted)
}

bool UHereiraSprinting::ShouldEnd()
{
	return bInterrupted || !GetWorld()->GetTimerManager().IsTimerActive(Duration);
}

void UHereiraSprinting::TickModifier(float DeltaTime)
{
	Target->Speed += Target->BaseSpeed * .35f;
}

void UHereiraSprinting::SetAbility(UHereiraSprint* SprintAbility)
{
	Ability = SprintAbility;
}

void UHereiraSprinting::Interrupt()
{
	bInterrupted = true;
}

void UHereiraSprinting::BeginModifier()
{
	GetWorld()->GetTimerManager().SetTimer(Duration, 3.f, false);
}

void UHereiraSprinting::EndModifier()
{
	if (bInterrupted || !Ability)
	{
		return;
	}
	Ability->ClientEndSprint();
}
