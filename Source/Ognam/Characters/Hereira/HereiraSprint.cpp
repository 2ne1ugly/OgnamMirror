// Copyright 2019 Ognam Studios. All Rights Reserved.#include "HereiraSprint.h"
#include "TimerManager.h"
#include "HereiraSprinting.h"
#include "Ognam/OgnamCharacter.h"
// Fill out your copyright notice in the Description page of Project Settings.

UHereiraSprint::UHereiraSprint()
{
	AbilityType = EAbilityType::Mobility;
	Cooldown = 8.f;
}

bool UHereiraSprint::ShouldShowNumber() const
{
	return Target->GetWorldTimerManager().IsTimerActive(SprintCooldown);
}

float UHereiraSprint::GetNumber() const
{
	return Target->GetWorldTimerManager().GetTimerRemaining(SprintCooldown);
}

void UHereiraSprint::OnButtonPressed()
{
	if (Target->GetWorldTimerManager().IsTimerActive(SprintCooldown) ||
		Target->GetModifier<UHereiraSprinting>() || 
		Target->HasStatusEffect(EStatusEffect::Silenced | EStatusEffect::Rooted))
	{
		return;
	}
	ServerStartSprint();
}

void UHereiraSprint::OnButtonReleased()
{
	ServerStopSprint();
}

void UHereiraSprint::ServerStartSprint_Implementation()
{
	if (Target->GetWorldTimerManager().IsTimerActive(SprintCooldown) ||
		Target->GetModifier<UHereiraSprinting>() ||
		Target->HasStatusEffect(EStatusEffect::Silenced | EStatusEffect::Rooted))
	{
		return;
	}
	Target->TakeAction(EActionNotifier::Focus);
	UHereiraSprinting* Sprinting = NewObject<UHereiraSprinting>(Target);
	Sprinting->SetAbility(this);
	Sprinting->RegisterComponent();
}

void UHereiraSprint::ServerStopSprint_Implementation()
{
	UHereiraSprinting* Sprinting = Target->GetModifier<UHereiraSprinting>();
	if (!Sprinting)
	{
		return;
	}
	Sprinting->Interrupt();
	Target->GetWorldTimerManager().SetTimer(SprintCooldown, Cooldown, false);
	ClientEndSprint();
}

void UHereiraSprint::StatusEffectApplied(EStatusEffect StatusEffect)
{
	//If status effect contains silenced
	if ((StatusEffect & EStatusEffect::Rooted) != EStatusEffect::None &&
		Target->GetModifier<UHereiraSprinting>())
	{
		ServerStopSprint_Implementation();
	}
}

void UHereiraSprint::ActionTaken(EActionNotifier ActionType)
{
}

void UHereiraSprint::ClientEndSprint_Implementation()
{
	Target->GetWorldTimerManager().SetTimer(SprintCooldown, Cooldown, false);
}