// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "HazelBlazingSpiritsAction.h"
#include "HazelBlazed.h"
#include "GameFramework/Actor.h"

UHazelBlazingSpiritsAction::UHazelBlazingSpiritsAction()
{
	PreDelayDuration = 0.f;
	PostDelayDuration = 0.f;

	ChannelStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
	ChannelDuration = 1.5f;
}

void UHazelBlazingSpiritsAction::EndChannel()
{
	if (GetOwner()->HasAuthority())
	{
		NewObject<UHazelBlazed>(GetOwner())->RegisterComponent();
	}
}
