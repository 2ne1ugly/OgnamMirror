// Fill out your copyright notice in the Description page of Project Settings.

#include "BloodhoundSteamLeapAction.h"
#include "Ognam/OgnamMacro.h"
#include "Ognam/OgnamCharacter.h"

UBloodhoundSteamLeapAction::UBloodhoundSteamLeapAction()
{
	PreDelayDuration = .2f;
	ChannelDuration = .5f;
	PostDelayDuration = .0f;

	PreDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
	ChannelStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
	PostDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;

	//Make walking mechanics
}

void UBloodhoundSteamLeapAction::EndChannel()
{
	float UpRatio = 1.f;

	if (Target->HasAuthority())
	{
		FVector LaunchDireciton = (GetOwner()->GetActorForwardVector() + FVector::UpVector * UpRatio).GetSafeNormal();
		Target->LaunchCharacter(LaunchDireciton * 1000.f, false, true);
	}
}
