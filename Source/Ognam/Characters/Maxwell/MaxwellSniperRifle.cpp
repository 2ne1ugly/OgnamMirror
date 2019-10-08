// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellSniperRifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerState.h"
#include "Ognam/ImpactDamage.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MaxwellAimDowned.h"
#include "MaxwellClaretStrikeCharged.h"
#include "MaxwellRecovering.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "MaxwellSniperTrail.h"
#include "MaxwellSniperRifleRecoil.h"

UMaxwellSniperRifle::UMaxwellSniperRifle()
{
	MaxAmmo = 8;
	Ammo = MaxAmmo;
	RoundsPerSecond = 2.5f;
	ReloadTime = 3.5f;

	BaseDamage = 50.f;

	ConstructorHelpers::FObjectFinder<USoundCue> SniperShotCue(TEXT("SoundCue'/Game/Sounds/Maxwell/maxwell_shot_cue2.maxwell_shot_cue2'"));
	ShotSoundCue = SniperShotCue.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> SniperShotParticle(TEXT("ParticleSystem'/Game/ParagonMurdock/FX/Particles/Abilities/Primary/FX/P_Murdock_Bullet_Trail_Smoke_Spline.P_Murdock_Bullet_Trail_Smoke_Spline'"));
	ParticleSystem = SniperShotParticle.Object;

	bBindSub = true;
}

void UMaxwellSniperRifle::BeginPlay()
{
	Super::BeginPlay();

	ShotTrail = NewObject<UParticleSystemComponent>(Target);
	ShotTrail->SetTemplate(ParticleSystem);
	ShotTrail->SetAutoActivate(false);
	ShotTrail->SetupAttachment(Target->GetRootComponent());
	ShotTrail->SetRelativeLocation(FVector::ZeroVector);
	ShotTrail->RegisterComponent();

	ShotSound = NewObject<UAudioComponent>(Target);
	ShotSound->SetAutoActivate(false);
	ShotSound->SetSound(ShotSoundCue);
	ShotSound->SetVolumeMultiplier(.345f);
	ShotSound->SetupAttachment(Target->GetRootComponent());
	ShotSound->SetRelativeLocation(FVector::ZeroVector);
	ShotSound->RegisterComponent();
}

void UMaxwellSniperRifle::FireBullet()
{
	FHitResult HitResult;
	Target->GetAimHitResult(HitResult, 0.f, 10000.f);

	//draw a ray from bullet spawn to that landing point
	FVector From = Target->GetMesh()->GetSocketLocation("BulletSpawn");
	FVector To;
	if (HitResult.bBlockingHit)
		To = HitResult.ImpactPoint;
	else
		To = HitResult.TraceEnd;

	NetPlayShotSound();

	//find direction to shoot bullets
	FVector Direction = To - From;
	Direction = Direction.GetSafeNormal();

	//shoot ray from camera to see where it should land.
	//UE_LOG(LogTemp, Warning, TEXT("X %f, Y %f, Z %f"), Direction.X, Direction.Y, Direction.Z);
	FHitResult BulletHit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Target);
	GetWorld()->LineTraceSingleByChannel(BulletHit, From, From + Direction * 10000.f, ECollisionChannel::ECC_GameTraceChannel1, Params);

	//DrawLine
	FVector BulletTo;
	if (BulletHit.bBlockingHit)
		BulletTo = BulletHit.ImpactPoint;
	else
		BulletTo = BulletHit.TraceEnd;
	NetDrawTrajectory(From, BulletTo);

	//Feedback recoil
	APlayerController* Controller = Target->GetController<APlayerController>();
	if (Controller)
	{
		Controller->ClientPlayCameraShake(UMaxwellSniperRifleRecoil::StaticClass());
	}

	float Damage = BaseDamage;
	UMaxwellClaretStrikeCharged* ClaretStrikeCharged = Target->GetModifier<UMaxwellClaretStrikeCharged>();
	if (ClaretStrikeCharged && ClaretStrikeCharged->Use())
	{
		NewObject<UMaxwellRecovering>(Target)->RegisterComponent();
		Damage = 80.f;
	}

	//Get Target's player state
	ACharacter* OtherCharacter = Cast<ACharacter>(BulletHit.Actor);
	if (!OtherCharacter)
	{
		return;
	}
	AOgnamPlayerState* OtherPlayerState = OtherCharacter->GetPlayerState<AOgnamPlayerState>();
	AOgnamPlayerState* PlayerState = Target->GetPlayerState<AOgnamPlayerState>();
	if (!OtherPlayerState || !PlayerState)
	{
		return;
	}

	if (OtherPlayerState->GetTeam() != PlayerState->GetTeam())
	{
		UGameplayStatics::ApplyPointDamage(OtherCharacter, Damage, Direction, BulletHit, Target->GetController(), Target, UImpactDamage::StaticClass());
	}
}

void UMaxwellSniperRifle::NetDrawTrajectory_Implementation(FVector From, FVector To)
{
	AMaxwellSniperTrail* Trail = GetWorld()->SpawnActor<AMaxwellSniperTrail>(From, (To - From).Rotation());
	Trail->SetActorScale3D(FVector((To - From).Size() / 95.f, 1.f, 1.f));
}

void UMaxwellSniperRifle::NetPlayShotSound_Implementation()
{
	ShotSound->Activate(true);
}

void UMaxwellSniperRifle::SubPressed()
{
	if (Target->HasStatusEffect(EStatusEffect::Unarmed))
	{
		return;
	}
	ServerToggleAimDown();
}

void UMaxwellSniperRifle::ServerToggleAimDown_Implementation()
{
	if (Target->HasStatusEffect(EStatusEffect::Unarmed))
	{
		return;
	}
	UMaxwellAimDowned* Modifier = Target->GetModifier<UMaxwellAimDowned>();
	if (Modifier)
	{
		Modifier->Interrupt();
	}
	else
	{
		NewObject<UMaxwellAimDowned>(Target)->RegisterComponent();
	}
}
