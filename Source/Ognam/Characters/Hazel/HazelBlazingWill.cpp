// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelBlazingWill.h"
#include "Ognam/OgnamCharacter.h"

UHazelBlazingWill::UHazelBlazingWill()
{
	AbilityType = EAbilityType::Mobility;
}

void UHazelBlazingWill::BeginPlay()
{
	Super::BeginPlay();

	Target->BaseSpeed *= 1.1f;
}
