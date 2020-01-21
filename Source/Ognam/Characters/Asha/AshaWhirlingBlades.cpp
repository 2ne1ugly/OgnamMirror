// Fill out your copyright notice in the Description page of Project Settings.


#include "AshaWhirlingBlades.h"
#include "AshaWhirlingBladesAction.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Ognam/OgnamCharacter.h"

// Asha 

UAshaWhirlingBlades::UAshaWhirlingBlades()
{
	AbilityType = EAbilityType::Mobility;
	Cooldown = 6.f;


	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Asha/WhirlingBlades.WhirlingBlades'"));
	Icon = IconTexture.Object;
}

void UAshaWhirlingBlades::ActivateAbility()
{
	NewObject<UAshaWhirlingBladesAction>(Target)->RegisterComponent();
}
