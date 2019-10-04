// Fill out your copyright notice in the Description page of Project Settings.

#include "BloodhoundPiercingThornsAction.h"
#include "BloodhoundThorns.h"
#include "Engine/World.h"
#include "Ognam/OgnamCharacter.h"

UBloodhoundPiercingThornsAction::UBloodhoundPiercingThornsAction()
{
	PreDelayDuration = .5f;
	ChannelDuration = 0.f;
	PostDelayDuration = .5f;

	PreDelayStatusEffect |= EStatusEffect::Silenced | EStatusEffect::Unarmed;
	PostDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Silenced | EStatusEffect::Unarmed;
}

void UBloodhoundPiercingThornsAction::TickPreDelay(float DeltaTime)
{
	Target->Speed /= 2.f;
}

void UBloodhoundPiercingThornsAction::BeginChannel()
{
	FVector Location = Target->GetActorLocation();
	FRotator Rotation = Target->GetActorForwardVector().Rotation();
	GetWorld()->SpawnActor<ABloodhoundThorns>(Location, Rotation)->SetReplicates(true);
}	
