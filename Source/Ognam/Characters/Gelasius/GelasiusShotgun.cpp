// Fill out your copyright notice in the Description page of Project Settings.


#include "GelasiusShotgun.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"

UGelasiusShotgun::UGelasiusShotgun()
{
	//MaxAmmo = 10;
	//Ammo = MaxAmmo;
	//RoundsPerSecond = 2.f;
	//ReloadTime = 4.f;

	//DamagePerPellet = 20.f;
	//PelletCount = 20;
	//Dist = 3000.f;
}

//void UGelasiusShotgun::FireBullet()
//{
//	Super::FireBullet();
//
//	FVector To = Target->Camera->GetComponentLocation() + Target->Camera->GetForwardVector() * 750.f;
//	FVector From = Target->GetMesh()->GetSocketLocation("BulletSpawn");
//
//	FVector Direction = To - From;
//
//	Direction = Direction.GetSafeNormal();
//
//	float Spread = PI / 16.f;
//	for (int i = 0; i < PelletCount; i++)
//	{
//		float RandAngle = FMath::RandRange(0.f, PI * 2.f);
//		float RandSpread = FMath::Tan(FMath::RandRange(0.f, Spread));
//		FVector BulletDirection = FVector(1, FMath::Cos(RandAngle) * RandSpread, FMath::Sin(RandAngle) * RandSpread).GetSafeNormal();
//		To = From + Direction.Rotation().RotateVector(BulletDirection) * 500.f;
//
//
////		const float Theta = FMath::RandRange(PI / -8.f, PI / 8.f);
////		float Zangle = FMath::RadiansToDegrees(PI / -16.f);
////		float z = FMath::RandRange(-FMath::Cos(Zangle), FMath::Cos(Zangle));
////		To = From + FVector(FMath::Sqrt(1 - z * z) * FMath::Sin(Theta), FMath::Sqrt(1 - z * z) * FMath::Cos(Theta), z) * 1000;
//		NetDrawTrajectory(From, To);
//	}
//}
//
//void UGelasiusShotgun::NetDrawTrajectory_Implementation(FVector From, FVector To)
//{
//	DrawDebugLine(GetWorld(), From, To, FColor::Red, false, 5.0f, 0, 3);
//}