// Fill out your copyright notice in the Description page of Project Settings.

#include "JeraDescending.h"
#include "Ognam/OgnamCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "JeraRadiantDiveDropPoint.h"

UJeraDescending::UJeraDescending()
{
	StatusEffect |= EStatusEffect::Unarmed | EStatusEffect::Silenced;
}

bool UJeraDescending::ShouldEnd()
{
	return !Target->GetCharacterMovement()->IsFalling();
}

void UJeraDescending::TickModifier(float DeltaTime)
{
	Target->AirControl += Target->BaseAirControl * 3;
}

void UJeraDescending::EndModifier()
{
	if (Target->HasAuthority())
	{
		FActorSpawnParameters Params;
		Params.Instigator = Target;
		Params.bNoFail = true;
		GetWorld()->SpawnActor<AJeraRadiantDiveDropPoint>(Target->GetActorLocation(), FRotator::ZeroRotator, Params)->SetReplicates(true);
	}
}
