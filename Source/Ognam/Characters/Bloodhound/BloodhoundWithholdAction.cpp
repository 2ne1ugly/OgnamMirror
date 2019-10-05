// Fill out your copyright notice in the Description page of Project Settings.

#include "BloodhoundWithholdAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/SkeletalMeshComponent.h"

UBloodhoundWithholdAction::UBloodhoundWithholdAction()
{
	PreDelayDuration = .5f;
	ChannelDuration = 2.5f;
	PostDelayDuration = .5f;

	PreDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
	ChannelStatusEffect |= EStatusEffect::Silenced | EStatusEffect::Unarmed;
	PostDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
}

void UBloodhoundWithholdAction::BeginChannel()
{
	HideTarget();
}

void UBloodhoundWithholdAction::TickChannel(float DeltaTime)
{
	Target->Speed *= .75f;
}

void UBloodhoundWithholdAction::EndChannel()
{
	ShowTarget();
}

void UBloodhoundWithholdAction::HideTarget_Implementation()
{
	Target->GetMesh()->SetVisibility(false);
}

void UBloodhoundWithholdAction::ShowTarget_Implementation()
{
	Target->GetMesh()->SetVisibility(true);
}
