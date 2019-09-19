// Fill out your copyright notice in the Description page of Project Settings.

#include "HereiraSprinting.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"
#include "UnrealNetwork.h"

UHereiraSprinting::UHereiraSprinting()
{
	StatusEffect |= EStatusEffect::Unarmed | EStatusEffect::Silenced;
	Duration = 3.f;
}

void UHereiraSprinting::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UHereiraSprinting, Ability, COND_InitialOnly);
	DOREPLIFETIME(UHereiraSprinting, bInterrupted)
}

bool UHereiraSprinting::ShouldEnd()
{
	return bInterrupted || Super::ShouldEnd();
}

void UHereiraSprinting::TickModifier(float DeltaTime)
{
	Target->Speed += Target->BaseSpeed;
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
	Super::BeginModifier();
}

void UHereiraSprinting::EndModifier()
{
	if (bInterrupted || !Ability)
	{
		return;
	}
	Ability->ClientEndSprint();
}
