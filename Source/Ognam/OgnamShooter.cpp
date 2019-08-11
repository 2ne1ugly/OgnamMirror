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

void AOgnamShooter::Shoot()
{
	if (Ammo > 0)
	{
		IsShooting = true;
		ServerUpdateShooting(IsShooting);
		Ammo--;
		ServerFireBullet();
	}
}

void AOgnamShooter::StopShoot()
{
	IsShooting = false;
	ServerUpdateShooting(IsShooting);
}


void AOgnamShooter::Reload()
{
	IsReloading = true;
	Ammo = 12;
	ServerUpdateReloading(IsReloading);
}

void AOgnamShooter::StopReload()
{
	IsReloading = false;
	ServerUpdateReloading(IsReloading);
}

void AOgnamShooter::Aim()
{
	IsAiming = true;
	ServerUpdateAiming(IsAiming);
}

void AOgnamShooter::StopAim()
{
	IsAiming = false;
	ServerUpdateAiming(IsAiming);
}


void AOgnamShooter::ServerFireBullet_Implementation()
{
	FVector RayFrom = Camera->GetComponentLocation();
	FVector RayTo = RayFrom + Camera->GetForwardVector() * 10000.f;
	FCollisionQueryParams Params(TEXT("cameraPath"), true, this);
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByProfile(HitResult, RayFrom, RayTo, TEXT("BlockAll"), Params);

	FVector From = GetMesh()->GetSocketLocation("BulletSpawn");
	FVector To;
	if (HitResult.bBlockingHit)
		To = HitResult.ImpactPoint;
	else
		To = HitResult.TraceEnd;
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
	DOREPLIFETIME(AOgnamShooter, IsAiming);
	DOREPLIFETIME(AOgnamShooter, IsShooting);
	DOREPLIFETIME(AOgnamShooter, IsReloading);
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
	if (IsAiming)
		Amount /= 2;
	Super::MoveForward(Amount);
}

void AOgnamShooter::MoveRight(float Amount)
{
	if (IsAiming)
		Amount /= 2;
	Super::MoveRight(Amount);
}

void AOgnamShooter::ServerUpdateAiming_Implementation(bool NewValue)
{
	IsAiming = NewValue;
}

void AOgnamShooter::ServerUpdateShooting_Implementation(bool NewValue)
{
	IsShooting = NewValue;
}

void AOgnamShooter::ServerUpdateReloading_Implementation(bool NewValue)
{
	IsReloading = NewValue;
}
