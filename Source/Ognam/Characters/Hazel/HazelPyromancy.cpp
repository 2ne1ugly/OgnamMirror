// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelPyromancy.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"
#include "HazelFireball.h"
UHazelPyromancy::UHazelPyromancy()
{
	bInfiniteAmmo = true;
	RoundsPerSecond = 4;
}

void UHazelPyromancy::FireBullet()
{
	if (!Target->HasAuthority())
	{
		return;
	}
	FHitResult Aim;
	Target->GetAimHitResult(Aim, 0.f, 10000.f);

	FVector From = Target->GetActorLocation() + FVector(0.f, 0.f, 60.f);
	FVector To;
	if (Aim.bBlockingHit)
		To = Aim.ImpactPoint;
	else
		To = Aim.TraceEnd;

	FVector Direction = To - From;
	FActorSpawnParameters Params;
	Params.bNoFail = true;
	Params.Instigator = Target;
	GetWorld()->SpawnActor<AHazelFireball>(From, Direction.Rotation(), Params)->SetReplicates(true);
}
