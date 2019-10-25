// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "HazelBlazingSpirits.h"
#include "HazelBlazingSpiritsAction.h"
#include "Ognam/OgnamCharacter.h"

UHazelBlazingSpirits::UHazelBlazingSpirits()
{
	AbilityType = EAbilityType::Utility;
	Cooldown = 15.f;
}

void UHazelBlazingSpirits::ActivateAbility()
{
	Target->TakeAction(EActionNotifier::Focus);
	NewObject<UHazelBlazingSpiritsAction>(GetOwner())->RegisterComponent();
}
