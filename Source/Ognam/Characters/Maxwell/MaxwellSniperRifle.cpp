// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellSniperRifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerState.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MaxwellAimDowned.h"
#include "MaxwellClaretStrikeCharged.h"
#include "MaxwellRecovering.h"

UMaxwellSniperRifle::UMaxwellSniperRifle()
{
	MaxAmmo = 5;
	Ammo = MaxAmmo;
	RoundsPerSecond = 3.f;
	ReloadTime = 6.f;

	BaseDamage = 35.f;
}

void UMaxwellSniperRifle::BeginPlay()
{
	Super::BeginPlay();

	SubPressHandle = Target->OnSubPressed.AddUObject(this, &UMaxwellSniperRifle::ToggleAimDown);
}

void UMaxwellSniperRifle::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	Target->OnSubPressed.Remove(SubPressHandle);
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

	//find direction to shoot bullets
	FVector Direction = To - From;
	Direction.Normalize();

	//shoot ray from camera to see where it should land.
	FHitResult BulletHit;
	GetWorld()->LineTraceSingleByProfile(BulletHit, From, From + Direction * 10000.f, TEXT("BlockAll"));

	//DrawLine
	FVector BulletTo;
	if (BulletHit.bBlockingHit)
		BulletTo = BulletHit.ImpactPoint;
	else
		BulletTo = BulletHit.TraceEnd;
	NetDrawTrajectory(From, BulletTo);

	float Damage = BaseDamage;
	UMaxwellClaretStrikeCharged* ClaretStrikeCharged = Target->GetModifier<UMaxwellClaretStrikeCharged>();
	if (ClaretStrikeCharged && ClaretStrikeCharged->Use())
	{
		NewObject<UMaxwellRecovering>(Target)->RegisterComponent();
		Damage = 100.f;
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
		UGameplayStatics::ApplyPointDamage(OtherCharacter, Damage, Direction, BulletHit, Target->GetController(), Target, nullptr);
	}
}

void UMaxwellSniperRifle::NetDrawTrajectory_Implementation(FVector From, FVector To)
{
	DrawDebugLine(GetWorld(), From, To, FColor::Red, false, 1.0f, 0, 3);
}

void UMaxwellSniperRifle::ToggleAimDown()
{
	ServerToggleAimDown();
}

void UMaxwellSniperRifle::ServerToggleAimDown_Implementation()
{
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