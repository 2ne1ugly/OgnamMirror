// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "BloodhoundHuntingHourAction.h"
#include "GameFramework/Actor.h"
#include "BloodhoundHuntingHourModifier.h"

UBloodhoundHuntingHourAction::UBloodhoundHuntingHourAction()
{
	PreDelayDuration = .2f;
	ChannelDuration = .7f;
	PostDelayDuration = .1f;

	PreDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
	ChannelStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
	PostDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
}

void UBloodhoundHuntingHourAction::EndChannel()
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	NewObject<UBloodhoundHuntingHourModifier>(GetOwner())->RegisterComponent();
}
