// Fill out your copyright notice in the Description page of Project Settings.


#include "AshaFanofKnivesAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "AshaDaggers.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Ognam/Weapon.h"

UAshaFanofKnivesAction::UAshaFanofKnivesAction()
{
	PreDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Unarmed | EStatusEffect::Silenced;
	PostDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Unarmed | EStatusEffect::Silenced;

	PreDelayDuration = .3f;
	ChannelDuration = .0f;
	PostDelayDuration = .2f;
}

void UAshaFanofKnivesAction::BeginChannel()
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

	for (float Angle = -30.f; Angle <= 60.f; Angle + 10.f)
	{

	}

	FActorSpawnParameters Params;
	Params.bNoFail = true;
	Params.Instigator = Target;
	GetWorld()->SpawnActor<AAshaDaggers>(From, Direction.Rotation(), Params)->SetReplicates(true);
}