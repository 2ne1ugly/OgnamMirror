// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "BloodhoundHuntingHour.h"
#include "BloodhoundHuntingHourAction.h"
#include "ConstructorHelpers.h"

UBloodhoundHuntingHour::UBloodhoundHuntingHour()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 7.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Bloodhound/piercing_roar.piercing_roar'"));
	Icon = IconTexture.Object;
}

void UBloodhoundHuntingHour::ActivateAbility()
{
	NewObject<UBloodhoundHuntingHourAction>(GetOwner())->RegisterComponent();
}
