// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "BloodhoundWithhold.h"
#include "BloodhoundWithholdAction.h"
#include "ConstructorHelpers.h"

UBloodhoundWithhold::UBloodhoundWithhold()
{
	AbilityType = EAbilityType::Utility;

	Cooldown = 9.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Bloodhound/detonation_switch.detonation_switch'"));
	Icon = IconTexture.Object;
}

void UBloodhoundWithhold::ActivateAbility()
{
	NewObject<UBloodhoundWithholdAction>(Target)->RegisterComponent();
}
