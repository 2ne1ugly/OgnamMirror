// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellSniperRifleAction.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "MaxwellSniperTrail.h"
#include "MaxwellSniperRifleRecoil.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Curves/CurveFloat.h"
#include "Ognam/Weapon.h"
#include "Ognam/OgnamStatics.h"
#include "Ognam/OgnamEnum.h"

UMaxwellSniperRifleAction::UMaxwellSniperRifleAction()
{
	ConstructorHelpers::FObjectFinder<USoundCue> SniperShotCue(TEXT("SoundCue'/Game/Sounds/Maxwell/maxwell_shot_cue2.maxwell_shot_cue2'"));
	ShotSoundCue = SniperShotCue.Object;

	ConstructorHelpers::FObjectFinder<UParticleSystem> SniperShotParticle(TEXT("ParticleSystem'/Game/ParagonMurdock/FX/Particles/Abilities/Primary/FX/P_Murdock_Bullet_Trail_Smoke_Spline.P_Murdock_Bullet_Trail_Smoke_Spline'"));
	ParticleSystem = SniperShotParticle.Object;

	ConstructorHelpers::FObjectFinder<UCurveFloat> DamageCurveCH(TEXT("CurveFloat'/Game/Curve/Maxwell/MaxwellSniperRifleDmg.MaxwellSniperRifleDmg'"));
	DamageCurve = DamageCurveCH.Object;

	float RoundsPerSecond = 1.4f;

	PreDelayDuration = 0.f;
	ChannelDuration = 0.f;
	PostDelayDuration = 1 / RoundsPerSecond;
}

void UMaxwellSniperRifleAction::BeginPlay()
{
	Super::BeginPlay();

	ShotTrail = NewObject<UParticleSystemComponent>(GetOwner());
	ShotTrail->SetTemplate(ParticleSystem);
	ShotTrail->SetAutoActivate(false);
	ShotTrail->SetupAttachment(GetOwner()->GetRootComponent());
	ShotTrail->SetRelativeLocation(FVector::ZeroVector);
	ShotTrail->RegisterComponent();

	ShotSound = NewObject<UAudioComponent>(GetOwner());
	ShotSound->SetAutoActivate(false);
	ShotSound->SetSound(ShotSoundCue);
	ShotSound->SetVolumeMultiplier(.345f);
	ShotSound->SetupAttachment(GetOwner()->GetRootComponent());
	ShotSound->SetRelativeLocation(FVector::ZeroVector);
	ShotSound->RegisterComponent();
}

void UMaxwellSniperRifleAction::BeginChannel()
{
	//this for now.
	if (!GetOwner()->HasAuthority())
	{
		return;
	}

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
	Direction = Target->GetWeapon()->ApplyRandomSpread(Direction);

	//shoot ray from camera to see where it should land.
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

	APawn* OtherPawn = Cast<APawn>(BulletHit.Actor);
	if (UOgnamStatics::CanDamage(GetWorld(), Target, OtherPawn, EDamageMethod::DamagesEnemy))
	{
		float Distance = (BulletTo - From).Size();
		float Damage = DamageCurve->GetFloatValue(Distance);

		if (BulletHit.BoneName == TEXT("Head"))
		{
			Damage *= 1.5;
		}
		UGameplayStatics::ApplyPointDamage(OtherPawn, Damage, Direction, BulletHit, Target->GetController(), Target, nullptr);
	}
}

void UMaxwellSniperRifleAction::TickPostDelay(float DeltaTime)
{
	Target->Speed *= .75f;
}

void UMaxwellSniperRifleAction::NetDrawTrajectory_Implementation(FVector From, FVector To)
{
	AMaxwellSniperTrail* Trail = GetWorld()->SpawnActor<AMaxwellSniperTrail>(From, (To - From).Rotation());
	Trail->SetActorScale3D(FVector((To - From).Size() / 95.f, 1.f, 1.f));
}

void UMaxwellSniperRifleAction::NetPlayShotSound_Implementation()
{
	ShotSound->Activate(true);
}
