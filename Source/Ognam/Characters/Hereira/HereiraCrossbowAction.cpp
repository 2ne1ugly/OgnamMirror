// Fill out your copyright notice in the Description page of Project Settings.

#include "HereiraCrossbowAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AudioComponent.h"
#include "HereiraArrow.h"
#include "Engine/World.h"
#include "Ognam/Weapon.h"
#include "ConstructorHelpers.h"
#include "Sound/SoundCue.h"

UHereiraCrossbowAction::UHereiraCrossbowAction()
{
	float RoundsPerSecond = 4.f;

	PreDelayDuration = 0.f;
	ChannelDuration = 0.f;
	PostDelayDuration = 1 / RoundsPerSecond;

	static ConstructorHelpers::FObjectFinder<USoundCue> ShotCue(TEXT("SoundCue'/Game/Sounds/Hereira/arrow_shot_cue.arrow_shot_cue'"));
	ShotSoundCue = ShotCue.Object;
}

void UHereiraCrossbowAction::BeginPlay()
{
	Super::BeginPlay();

	ShotSound = NewObject<UAudioComponent>(GetOwner());
	ShotSound->SetupAttachment(GetOwner()->GetRootComponent());
	ShotSound->SetRelativeLocation(FVector::ZeroVector);
	ShotSound->SetSound(ShotSoundCue);
	ShotSound->SetAutoActivate(false);
	ShotSound->SetIsReplicated(true);
}

void UHereiraCrossbowAction::BeginChannel()
{
	if (!GetOwner()->HasAuthority())
	{
		return;
	}
	FHitResult Aim;
	Target->GetAimHitResult(Aim, 0.f, 10000.f);

	FVector From = Target->GetMesh()->GetSocketLocation("BulletSpawn");
	FVector To;
	if (Aim.bBlockingHit)
	{
		To = Aim.ImpactPoint;
	}
	else
	{
		To = Aim.TraceEnd;
	}

	FVector Direction = To - From;
	Direction = Target->GetWeapon()->ApplyRandomSpread(Direction);

	FActorSpawnParameters Params;
	Params.bNoFail = true;
	Params.Instigator = Target;
	GetWorld()->SpawnActor<AHereiraArrow>(From, Direction.Rotation(), Params)->SetReplicates(true);
	ShotSound->Activate();
}
