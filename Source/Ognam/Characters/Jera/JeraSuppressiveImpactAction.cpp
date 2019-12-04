// Fill out your copyright notice in the Description page of Project Settings.


#include "JeraSuppressiveImpactAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "JeraCrystalSpear.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

UJeraSuppressiveImpactAction::UJeraSuppressiveImpactAction()
{
	PreDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Unarmed | EStatusEffect::Silenced;
	PostDelayStatusEffect |= EStatusEffect::Rooted | EStatusEffect::Unarmed | EStatusEffect::Silenced;

	PreDelayDuration = .3f;
	ChannelDuration = .0f;
	PostDelayDuration = .2f;

	static ConstructorHelpers::FObjectFinder<USoundCue> BuildupSoundFinder(TEXT("SoundCue'/Game/Sounds/Jera/ice_forming_Cue.ice_forming_Cue'"));
	BuildupSound = BuildupSoundFinder.Object;
}

void UJeraSuppressiveImpactAction::EndChannel()
{
	UAudioComponent* IceForming = NewObject<UAudioComponent>(Target);
	IceForming->SetupAttachment(Target->GetRootComponent());
	IceForming->SetRelativeLocation(FVector::ZeroVector);
	IceForming->SetAutoActivate(false);
	IceForming->SetSound(BuildupSound);
	IceForming->Activate();
	IceForming->bAutoDestroy = true;
	IceForming->RegisterComponent();
	if (!Target->HasAuthority())
	{
		return;
	}
	FHitResult Aim;
	Target->GetAimHitResult(Aim, 0.f, 10000.f);

	FVector From = Target->GetMesh()->GetSocketLocation("BulletSpawn");
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
