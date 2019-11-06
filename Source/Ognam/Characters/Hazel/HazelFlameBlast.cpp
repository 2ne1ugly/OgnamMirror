// Fill out your copyright notice in the Description page of Project Settings.

#include "HazelFlameBlast.h"
#include "HazelFlameBlastAction.h"
#include "ConstructorHelpers.h"

UHazelFlameBlast::UHazelFlameBlast()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 6.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Hazel/flame_pillar.flame_pillar'"));
	Icon = IconTexture.Object;
}

void UHazelFlameBlast::ActivateAbility()
{
	NewObject<UHazelFlameBlastAction>(Target)->RegisterComponent();
}
