
#include "HereiraSprint.h"
#include "TimerManager.h"
#include "HereiraSprinting.h"
#include "Ognam/OgnamCharacter.h"
// Fill out your copyright notice in the Description page of Project Settings.

UHereiraSprint::UHereiraSprint()
{
	AbilityType = EAbilityType::Mobility;
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
	if (Target->GetWorldTimerManager().IsTimerActive(SprintCooldown) || Target->GetModifier<UHereiraSprinting>())
	{
		return;
	}
	ServerStartSprint();
}

void UHereiraSprint::OnButtonReleased()
{
	if (!Target->GetModifier<UHereiraSprinting>())
	{
		return;
	}
	ServerStopSprint();
}

void UHereiraSprint::ServerStartSprint_Implementation()
{
	if (Target->GetWorldTimerManager().IsTimerActive(SprintCooldown) || Target->GetModifier<UHereiraSprinting>())
	{
		return;
	}
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
	Target->GetWorldTimerManager().SetTimer(SprintCooldown, 6.f, false);
	ClientEndSprint();
}

void UHereiraSprint::ClientEndSprint_Implementation()
{
	Target->GetWorldTimerManager().SetTimer(SprintCooldown, 6.f, false);
}