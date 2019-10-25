// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "HazelBlazingSpirits.h"
#include "HazelBlazingSpiritsAction.h"
#include "Ognam/OgnamCharacter.h"
#include "ConstructorHelpers.h"

UHazelBlazingSpirits::UHazelBlazingSpirits()
{
	AbilityType = EAbilityType::Utility;
	Cooldown = 15.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Hazel/ifrits_blessing.ifrits_blessing'"));
	Icon = IconTexture.Object;
}

void UHazelBlazingSpirits::ActivateAbility()
{
	Target->TakeAction(EActionNotifier::Focus);
	NewObject<UHazelBlazingSpiritsAction>(GetOwner())->RegisterComponent();
}
