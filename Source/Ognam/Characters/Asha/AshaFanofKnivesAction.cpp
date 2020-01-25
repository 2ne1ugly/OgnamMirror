// Fill out your copyright notice in the Description page of Project Settings.


#include "AshaFanofKnivesAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "AshaFanDaggers.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "Ognam/Weapon.h"

UAshaFanofKnivesAction::UAshaFanofKnivesAction()
{
	PreDelayDuration = .05f;
	ChannelDuration = .1f;
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

	FActorSpawnParameters Params;
	Params.bNoFail = true;
	Params.Instigator = Target;

	float Angle = -5.f;
	for (int i = 0; i < 5; i++, Angle += 2.5f)
	{
		FVector ZAxisRotatedVector = Direction.RotateAngleAxis(Angle, FVector(0, 0, 1));
		GetWorld()->SpawnActor<AAshaFanDaggers>(From, ZAxisRotatedVector.Rotation(), Params)->SetReplicates(true);
	}
}