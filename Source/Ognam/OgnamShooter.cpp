// Fill out your copyright notice in the Description page of Project Settings.

#include "OgnamShooter.h"
#include "OgnamCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "ConstructorHelpers.h"
#include "Animation/AnimBlueprint.h"
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
	}
}

void AOgnamShooter::StopShoot()
{
	IsShooting = false;
}


void AOgnamShooter::Reload()
{
	IsReloading = true;
}

void AOgnamShooter::Aim()
{
	IsAiming = true;
}

void AOgnamShooter::StopAim()
{
	IsAiming = false;
}


void AOgnamShooter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamShooter, Ammo);
	DOREPLIFETIME(AOgnamShooter, MaxAmmo);
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