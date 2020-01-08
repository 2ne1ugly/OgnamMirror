// Fill out your copyright notice in the Description page of Project Settings.

#include "PromptActiveAbility.h"
#include "OgnamCharacter.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "OgnamGameState.h"
#include "OgnamMacro.h"
UPromptActiveAbility::UPromptActiveAbility()
{
	UnacceptedStatusEffects = { EStatusEffect::Silenced };
}

bool UPromptActiveAbility::ShouldShowNumber() const
{
	return Target->GetWorldTimerManager().IsTimerActive(CooldownTimer);
}

float UPromptActiveAbility::GetNumber() const
{
	return Target->GetWorldTimerManager().GetTimerRemaining(CooldownTimer);
}

void UPromptActiveAbility::OnButtonPressed()
{
	if (Target->GetWorldTimerManager().IsTimerActive(CooldownTimer))
	{
		return;
	}
	for (const EStatusEffect& StatusEffect : UnacceptedStatusEffects)
	{
		if (Target->HasStatusEffect(StatusEffect))
		{
			return;
		}
	}
	ServerOnButtonPressed();
}

void UPromptActiveAbility::ServerOnButtonPressed_Implementation()
{
	if (Target->GetWorldTimerManager().IsTimerActive(CooldownTimer))
	{
		return;
	}
	for (const EStatusEffect& StatusEffect : UnacceptedStatusEffects)
	{
		if (Target->HasStatusEffect(StatusEffect))
		{
			return;
		}
	}
	ActivateAbility();
	Target->GetWorldTimerManager().SetTimer(CooldownTimer, Cooldown, false);
	ClientFeedbackUsed();
}

void UPromptActiveAbility::ActivateAbility()
{
}

void UPromptActiveAbility::ClientFeedbackUsed_Implementation()
{
	Target->GetWorldTimerManager().SetTimer(CooldownTimer, Cooldown, false);
}

	