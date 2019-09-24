// Fill out your copyright notice in the Description page of Project Settings.


#include "GelasiusShotgun.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"

UGelasiusShotgun::UGelasiusShotgun()
{
	MaxAmmo = 4;
	Ammo = MaxAmmo;
	RoundsPerSecond = 2.f;
	ReloadTime = 4.f;

	DamagePerPellet = 20.f;
	PelletCount = 20;

}

void UGelasiusShotgun::FireBullet()
{
	Super::FireBullet();

	FVector To = Target->Camera->GetComponentLocation() + Target->Camera->GetForwardVector() * 10000;
	FVector From = Target->GetMesh()->GetSocketLocation("BulletSpawn");

	FVector Direction = To - From;

	Direction = Direction.GetSafeNormal();

	for (int i = 0; i < PelletCount; i++)
	{
		const float Theta = FMath::RandRange(0.f, PI / 8.f);
		float z = FMath::RandRange(-.2f, .2f);
		To = From + FVector(FMath::Sqrt(1 - z * z) * FMath::Cos(Theta), FMath::Sqrt(1 - z * z) * FMath::Sin(Theta), z) * 1000;
		NetDrawTrajectory(From, To);
	}
}

void UGelasiusShotgun::NetDrawTrajectory_Implementation(FVector From, FVector To)
{
	DrawDebugLine(GetWorld(), From, To, FColor::Red, false, 5.0f, 0, 3);
}