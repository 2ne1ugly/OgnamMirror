// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "BloodhoundImpactShotgun.h"
#include "BloodhoundImpactShotgunAction.h"
#include "ConstructorHelpers.h"

UBloodhoundImpactShotgun::UBloodhoundImpactShotgun()
{
	AbilityType = EAbilityType::Special;
	Cooldown = 5.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Bloodhound/shotgun.shotgun'"));
	Icon = IconTexture.Object;
}

void UBloodhoundImpactShotgun::ActivateAbility()
{
	NewObject<UBloodhoundImpactShotgunAction>(GetOwner())->RegisterComponent();
}
