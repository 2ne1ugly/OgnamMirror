// Fill out your copyright notice in the Description page of Project Settings.


#include "AshaFanofKnives.h"
#include "AshaFanofKnivesAction.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Ognam/OgnamCharacter.h"

UAshaFanofKnives::UAshaFanofKnives()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 4.f;

	//static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Jera/icicle_throw.icicle_throw'"));
	//Icon = IconTexture.Object;
}

void UAshaFanofKnives::ActivateAbility()
{
	NewObject<UAshaFanofKnivesAction>(Target)->RegisterComponent();
}