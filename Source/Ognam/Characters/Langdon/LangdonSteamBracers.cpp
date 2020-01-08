// Fill out your copyright notice in the Description page of Project Settings.


#include "LangdonSteamBracers.h"
#include "LangdonSteamBracersModifier.h"
ULangdonSteamBracers::ULangdonSteamBracers()
{
	AbilityType = EAbilityType::Mobility;
	Cooldown = 15.f;
	UnacceptedStatusEffects.Add(EStatusEffect::Rooted);

	//static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Jera/super_jump.super_jump'"));
	//Icon = IconTexture.Object;
}

void ULangdonSteamBracers::ActivateAbility()
{
	NewObject<ULangdonSteamBracersModifier>(Target)->RegisterComponent();
}
