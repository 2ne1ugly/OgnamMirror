// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "HazelDisruptiveBurst.h"
#include "HazelBurstAction.h"
#include "HazelEnhancedBurstAction.h"
#include "HazelBlazed.h"
#include "ConstructorHelpers.h"

UHazelDisruptiveBurst::UHazelDisruptiveBurst()
{
	AbilityType = EAbilityType::Special;
	Cooldown = 10.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Hazel/rapid_fire.rapid_fire'"));
	Icon = IconTexture.Object;
}

void UHazelDisruptiveBurst::ActivateAbility()
{
	//Make this more smooth.
	if (Target->GetModifier<UHazelBlazed>())
	{
		NewObject<UHazelEnhancedBurstAction>(Target)->RegisterComponent();
	}
	else
	{
		NewObject<UHazelBurstAction>(Target)->RegisterComponent();
	}
}
