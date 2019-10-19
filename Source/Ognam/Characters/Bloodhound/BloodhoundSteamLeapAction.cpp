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

void UBloodhoundSteamLeapAction::TickChannel(float DeltaTime)
{
	//TODO: change this into root motion.
	Target->AddMovementInput(GetOwner()->GetActorForwardVector(), 1.f);
	Target->Acceleration += Target->BaseAcceleration * 1.5f;
	Target->Speed += Target->BaseSpeed * .5f;
}


void UBloodhoundSteamLeapAction::BeginPostDelay()
{
	float UpRatio = 1.5f;

	if (Target->HasAuthority())
	{
		FVector LaunchDireciton = (GetOwner()->GetActorForwardVector() + FVector::UpVector * UpRatio).GetSafeNormal();
		Target->LaunchCharacter(LaunchDireciton * 500.f, false, true);
	}
}
