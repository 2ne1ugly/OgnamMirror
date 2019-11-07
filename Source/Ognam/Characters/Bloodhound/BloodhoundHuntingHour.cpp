// Fill out your copyright notice in the Description page of Project Settings.


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
