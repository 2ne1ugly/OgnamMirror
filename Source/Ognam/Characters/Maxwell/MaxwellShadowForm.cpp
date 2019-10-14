// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellShadowForm.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UMaxwellShadowForm::UMaxwellShadowForm()
{
	StatusEffect |= EStatusEffect::Unarmed | EStatusEffect::Silenced | EStatusEffect::Unbreakable;
	Duration = .4f;
}

void UMaxwellShadowForm::TickModifier(float DeltaTime)
{
	Target->Acceleration += Target->BaseAcceleration * 1;
	Target->Speed += Target->BaseSpeed * 1;
}

void UMaxwellShadowForm::BeginModifier()
{
	Super::BeginModifier();
	Target->GetCharacterMovement()->Velocity.Z = 0.f;
	Target->GetCharacterMovement()->MovementMode = MOVE_Falling;
}
