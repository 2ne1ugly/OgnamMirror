// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelBlazingSpirits.h"
#include "HazelBlazingSpiritsAction.h"
#include "Ognam/OgnamCharacter.h"

UHazelBlazingSpirits::UHazelBlazingSpirits()
{
	AbilityType = EAbilityType::Utility;
	Cooldown = 15.f;
}

void UHazelBlazingSpirits::ActivateAbility()
{
	Target->TakeAction(EActionNotifier::Focus);
	NewObject<UHazelBlazingSpiritsAction>(GetOwner())->RegisterComponent();
}
