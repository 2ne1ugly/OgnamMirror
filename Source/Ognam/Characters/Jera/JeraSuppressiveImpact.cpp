// Fill out your copyright notice in the Description page of Project Settings.

#include "JeraSuppressiveImpact.h"
#include "JeraCrystalSpear.h"
#include "Engine/World.h"
#include "Ognam/OgnamCharacter.h"
#include "Camera/CameraComponent.h"
UJeraSuppressiveImpact::UJeraSuppressiveImpact()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 1.f;
}

void UJeraSuppressiveImpact::ActivateAbility()
{
	FHitResult Aim;
	Target->GetAimHitResult(Aim, 0.f, 10000.f);

	FVector From = Target->GetActorLocation();
	FVector To;
	if (Aim.bBlockingHit)
		To = Aim.ImpactPoint;
	else
		To = Aim.TraceEnd;

	FVector Direction = To - From;

	FActorSpawnParameters Params;
	Params.bNoFail = true;
	Params.Instigator = Target;
	GetWorld()->SpawnActor<AJeraCrystalSpear>(From, Direction.Rotation(), Params)->SetReplicates(true);
}
