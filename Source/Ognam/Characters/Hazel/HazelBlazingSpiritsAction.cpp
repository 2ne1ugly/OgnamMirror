// Fill out your copyright notice in the Description page of Project Settings.


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
