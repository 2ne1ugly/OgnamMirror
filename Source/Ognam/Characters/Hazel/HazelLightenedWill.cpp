// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelLightenedWill.h"
#include "Ognam/OgnamCharacter.h"

UHazelLightenedWill::UHazelLightenedWill()
{
	AbilityType = EAbilityType::Mobility;
}

void UHazelLightenedWill::BeginPlay()
{
	Super::BeginPlay();

	Target->BaseSpeed *= 1.1f;
}
