// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellVaultModifier.h"
#include "Ognam/OgnamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UMaxwellVaultModifier::UMaxwellVaultModifier()
{

}

bool UMaxwellVaultModifier::ShouldEnd()
{
	return !Target->GetCharacterMovement()->IsFalling() && Target->GetVelocity().Z <= 0;
}

void UMaxwellVaultModifier::TickModifier(float DeltaTime)
{
	Target->Gravity += Target->BaseGravity;
	Target->AirControl += Target->BaseAirControl * 3;
}
