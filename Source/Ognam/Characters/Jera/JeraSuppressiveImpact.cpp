// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "JeraSuppressiveImpact.h"
#include "JeraSuppressiveImpactAction.h"
#include "ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

UJeraSuppressiveImpact::UJeraSuppressiveImpact()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 4.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Jera/icicle_throw.icicle_throw'"));
	Icon = IconTexture.Object;


}

void UJeraSuppressiveImpact::ActivateAbility()
{
	NewObject<UJeraSuppressiveImpactAction>(Target)->RegisterComponent();
}
