// Copyright 2019 Ognam Studios. All Rights Reserved.

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
	Target->Gravity += Target->BaseGravity * 2;
	Target->AirControl += Target->BaseAirControl * 3;
}
