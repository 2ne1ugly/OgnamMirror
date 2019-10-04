// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelFlameBlast.h"
#include "HazelFlamePillar.h"
#include "HazelEnhancedFlamePillar.h"
#include "HazelBlazed.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"

UHazelFlameBlast::UHazelFlameBlast()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 6.f;
}

void UHazelFlameBlast::ActivateAbility()
{
	FHitResult AimHit;
	Target->GetAimHitResult(AimHit, 0.f, 2000.f);
	FVector From;
	if (AimHit.bBlockingHit)
		From = AimHit.ImpactPoint;
	else
		From = AimHit.TraceEnd;

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);

	FHitResult DropHit;
	GetWorld()->LineTraceSingleByObjectType(DropHit, From, From + FVector::DownVector * 10000.f, ObjectParams);


	FActorSpawnParameters Params;
	Params.bNoFail = true;
	Params.Instigator = Target;

	if (Target->GetModifier<UHazelBlazed>())
	{
		GetWorld()->SpawnActor<AHazelEnhancedFlamePillar>(DropHit.Location, FRotator::ZeroRotator, Params)->SetReplicates(true);
	}
	else
	{
		GetWorld()->SpawnActor<AHazelFlamePillar>(DropHit.Location, FRotator::ZeroRotator, Params)->SetReplicates(true);
	}
}
