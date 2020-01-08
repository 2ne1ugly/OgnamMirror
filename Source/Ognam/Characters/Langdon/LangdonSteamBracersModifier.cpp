// Fill out your copyright notice in the Description page of Project Settings.


#include "LangdonSteamBracersModifier.h"
#include "Ognam/OgnamCharacter.h"

ULangdonSteamBracersModifier::ULangdonSteamBracersModifier()
{
	PreDelayDuration = .5f;
	ChannelDuration = 6.f;
	PostDelayDuration = .0f;

	PreDelayStatusEffect = { EStatusEffect::Rooted, EStatusEffect::Silenced, EStatusEffect::Unarmed };
}

void ULangdonSteamBracersModifier::TickChannel(float DeltaTime)
{
	Target->Speed += Target->BaseSpeed * .3f;
}
