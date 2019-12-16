// Fill out your copyright notice in the Description page of Project Settings.


#include "AshaThrowingDaggersAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Ognam/Weapon.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "AshaDaggers.h"

UAshaThrowingDaggersAction::UAshaThrowingDaggersAction()
{
	float RoundsPerSecond = 3.f;

	PreDelayDuration = .0f;
	ChannelDuration = .0f;
	PostDelayDuration = 1.f / RoundsPerSecond;

	BaseDamage = 30.f;
}

void UAshaThrowingDaggersAction::BeginChannel()
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	FHitResult Aim;
	Target->GetAimHitResult(Aim, 0.f, 10000.f);

	// find trajectory of weapon
	FVector From = Target->GetActorLocation() + FVector(0.f, 0.f, 60.f);
	FVector To;
	if (Aim.bBlockingHit)
		To = Aim.ImpactPoint;
	else
		To = Aim.TraceEnd;

	FVector Direction = To - From;
	Direction = Target->GetWeapon()->ApplyRandomSpread(Direction);

	FActorSpawnParameters Params;
	Params.bNoFail = true;
	Params.Instigator = Target;
	GetWorld()->SpawnActor<AAshaDaggers>(From, Direction.Rotation(), Params)->SetReplicates(true);
}
