// Fill out your copyright notice in the Description page of Project Settings.

#include "BloodhoundEtchedStalkerAction.h"
#include "BloodhoundStalking.h"
#include "GameFramework/Actor.h"

UBloodhoundEtchedStalkerAction::UBloodhoundEtchedStalkerAction()
{
}

void UBloodhoundEtchedStalkerAction::EndChannel()
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	NewObject<UBloodhoundStalking>(GetOwner())->RegisterComponent();
}
