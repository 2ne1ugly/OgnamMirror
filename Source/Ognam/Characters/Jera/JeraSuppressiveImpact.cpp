// Fill out your copyright notice in the Description page of Project Settings.

#include "JeraSuppressiveImpact.h"
#include "JeraSuppressiveImpactAction.h"
#include "ConstructorHelpers.h"

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
