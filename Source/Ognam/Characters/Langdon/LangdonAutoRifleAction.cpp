// Fill out your copyright notice in the Description page of Project Settings.

#include "LangdonAutoRifleAction.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Ognam/Weapon.h"
#include "Ognam/OgnamPlayerstate.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ULangdonAutoRifleAction::ULangdonAutoRifleAction()
{
	float RoundsPerSecond = 4;

	PreDelayDuration = .0f;
	ChannelDuration = .0f;
	PostDelayDuration = 1.f / RoundsPerSecond;

	BaseDamage = 20.f;
}

void ULangdonAutoRifleAction::BeginChannel()
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
	//APlayerController* Controller = Target->GetController<APlayerController>();
	//if (Controller)
	//{
	//	Controller->ClientPlayCameraShake(UMaxwellSniperRifleRecoil::StaticClass());
	//}

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
		UGameplayStatics::ApplyPointDamage(OtherCharacter, BaseDamage, Direction, BulletHit, Target->GetController(), Target, nullptr);
	}
}

void ULangdonAutoRifleAction::NetDrawTrajectory_Implementation(FVector From, FVector To)
{
	DrawDebugLine(GetWorld(), From, To, FColor::Red, false, .5f);
}
