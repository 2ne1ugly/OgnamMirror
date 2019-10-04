// Fill out your copyright notice in the Description page of Project Settings.

#include "BloodhoundEtchedStalkerAction.h"
#include "BloodhoundStalking.h"
#include "GameFramework/Actor.h"

UBloodhoundEtchedStalkerAction::UBloodhoundEtchedStalkerAction()
{
	PreDelayDuration = .2f;
	ChannelDuration = 1.f;
	PostDelayDuration = .2f;

	PreDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
	ChannelStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
	PostDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
}

void UBloodhoundEtchedStalkerAction::EndChannel()
{
	NewObject<UBloodhoundStalking>(GetOwner())->RegisterComponent();
}
