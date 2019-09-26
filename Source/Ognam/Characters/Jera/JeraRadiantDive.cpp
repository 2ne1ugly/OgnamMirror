// Fill out your copyright notice in the Description page of Project Settings.


#include "JeraRadiantDive.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "JeraDescending.h"
#include "Camera/CameraComponent.h"
UJeraRadiantDive::UJeraRadiantDive()
{
	AbilityType = EAbilityType::Mobility;
	Cooldown = 1.f;
	UnacceptedStatusEffects |= EStatusEffect::Rooted;
}

void UJeraRadiantDive::ActivateAbility()
{
	Target->TakeAction(EActionType::Focus);

	FVector FacingDirection = Target->Camera->GetForwardVector();
	FacingDirection.Z = FMath::Min(FacingDirection.Z, 0.f);
	FacingDirection.Z += 1.5;

	Target->GetCharacterMovement()->Velocity.Z = 0.f;
	Target->GetCharacterMovement()->AddImpulse(FacingDirection.GetSafeNormal() * 160000.f);
	Target->GetCharacterMovement()->MovementMode = MOVE_Falling;
	NewObject<UJeraDescending>(Target)->RegisterComponent();
}
