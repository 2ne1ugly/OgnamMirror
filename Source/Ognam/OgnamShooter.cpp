// Fill out your copyright notice in the Description page of Project Settings.

#include "OgnamShooter.h"
#include "OgnamCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "ConstructorHelpers.h"
#include "Animation/AnimBlueprint.h"
#include "OgnamProjectile.h"
#include "UnrealNetwork.h"

AOgnamShooter::AOgnamShooter()
{
	Ammo = 12;
	MaxAmmo = 12;
}

int32 AOgnamShooter::GetAmmo() const
{
	return Ammo;
}

int32 AOgnamShooter::GetMaxAmmo() const
{
	return MaxAmmo;
}

bool AOgnamShooter::GetIsAiming() const
{
	return bIsAiming;
}

bool AOgnamShooter::GetIsShooting() const
{
	return bIsShooting;
}

bool AOgnamShooter::GetIsReloading() const
{
	return bIsReloading;
}

void AOgnamShooter::Shoot()
{
	if (Ammo > 0)
	{
		bIsShooting = true;
		ServerSetIsShooting(bIsShooting);
		Ammo--;
		ServerFireBullet();
	}
}

void AOgnamShooter::StopShoot()
{
	bIsShooting = false;
	ServerSetIsShooting(bIsShooting);
}


void AOgnamShooter::Reload()
{
	bIsReloading = true;
	Ammo = 12;
	ServerSetIsReloading(bIsReloading);
}

void AOgnamShooter::StopReload()
{
	bIsReloading = false;
	ServerSetIsReloading(bIsReloading);
}

void AOgnamShooter::Aim()
{
	bIsAiming = true;
	ServerSetIsAiming(bIsAiming);
}

void AOgnamShooter::StopAim()
{
	bIsAiming = false;
	ServerSetIsAiming(bIsAiming);
}

void AOgnamShooter::ServerFireBullet_Implementation()
{
	FHitResult HitResult;
	GetAimHitResult(HitResult);

	//draw a ray from bullet spawn to that landing point
	FVector From = GetMesh()->GetSocketLocation("BulletSpawn");
	FVector To;
	if (HitResult.bBlockingHit)
		To = HitResult.ImpactPoint;
	else
		To = HitResult.TraceEnd;

	//find direction to shoot bullets
	FVector Direction = To - From;
	Direction.Normalize();
	FireBullet(From, Direction);
}

void AOgnamShooter::FireBullet_Implementation(FVector From, FVector Direction)
{
	AOgnamProjectile* Projectile = GetWorld()->SpawnActor<AOgnamProjectile>(From, Direction.Rotation());
	Projectile->SetInitialDirection(Direction);
	Projectile->SetController(GetController());
}

void AOgnamShooter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamShooter, Ammo);
	DOREPLIFETIME(AOgnamShooter, MaxAmmo);
	DOREPLIFETIME(AOgnamShooter, bIsAiming);
	DOREPLIFETIME(AOgnamShooter, bIsShooting);
	DOREPLIFETIME(AOgnamShooter, bIsReloading);
}

void AOgnamShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AOgnamShooter::Shoot);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AOgnamShooter::StopShoot);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AOgnamShooter::Aim);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AOgnamShooter::StopAim);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AOgnamShooter::Reload);
}

void AOgnamShooter::MoveForward(float Amount)
{
	if (bIsAiming)
		Amount /= 2;
	Super::MoveForward(Amount);
}

void AOgnamShooter::MoveRight(float Amount)
{
	if (bIsAiming)
		Amount /= 2;
	Super::MoveRight(Amount);
}

void AOgnamShooter::ServerSetIsAiming_Implementation(bool NewValue)
{
	bIsAiming = NewValue;
}

void AOgnamShooter::ServerSetIsShooting_Implementation(bool NewValue)
{
	bIsShooting = NewValue;
}

void AOgnamShooter::ServerSetIsReloading_Implementation(bool NewValue)
{
	bIsReloading = NewValue;
}
