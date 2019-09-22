// Fill out your copyright notice in the Description page of Project Settings.


#include "JeraRadiantDive.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "JeraDescending.h"

UJeraRadiantDive::UJeraRadiantDive()
{
	AbilityType = EAbilityType::Mobility;
	Cooldown = 1.f;
}

void UJeraRadiantDive::ActivateAbility()
{
	Target->GetCharacterMovement()->AddImpulse(FVector::UpVector * 100000.f + Target->GetActorForwardVector() * 100000.f);
	NewObject<UJeraDescending>(Target)->RegisterComponent();
}
