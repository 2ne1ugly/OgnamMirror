// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellSniperRifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "Ognam/OgnamPlayerState.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

UMaxwellSniperRifle::UMaxwellSniperRifle()
{
	MaxAmmo = 5;
	Ammo = MaxAmmo;
	RoundsPerSecond = 3.f;
	ReloadTime = 6.f;
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
	DrawDebugLine(GetWorld(), From, BulletTo, FColor::Red, false, 1.0f, 0, 10);

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
		UGameplayStatics::ApplyPointDamage(OtherCharacter, 35.f, Direction, BulletHit, Target->GetController(), Target, nullptr);
	}
}
