// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelFlameBlast.h"
#include "HazelFlamePillar.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"

UHazelFlameBlast::UHazelFlameBlast()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 6.f;
}

void UHazelFlameBlast::ActivateAbility()
{
	FActorSpawnParameters Params;
	Params.bNoFail = true;
	Params.Instigator = Target;
	GetWorld()->SpawnActor<AHazelFlamePillar>(Target->GetActorLocation(), FRotator::ZeroRotator, Params)->SetReplicates(true);
}
