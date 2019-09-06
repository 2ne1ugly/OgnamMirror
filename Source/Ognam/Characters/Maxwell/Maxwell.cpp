// Fill out your copyright notice in the Description page of Project Settings.

#include "Maxwell.h"
#include "Components/InputComponent.h"
AMaxwell::AMaxwell()
{

}

void AMaxwell::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Basic"), IE_Pressed, this, &AMaxwell::StartCharge);
	PlayerInputComponent->BindAction(TEXT("Basic"), IE_Released, this, &AMaxwell::FireBullet);
	PlayerInputComponent->BindAction(TEXT("Sub"), IE_Pressed, this, &AMaxwell::ToggleAimDown);
	PlayerInputComponent->BindAction(TEXT("Mobility"), IE_Pressed, this, &AMaxwell::ShadowShift);
}

void AMaxwell::StartCharge()
{
}

void AMaxwell::ServerStartCharge_Implementation()
{
}

void AMaxwell::FireBullet()
{
}

void AMaxwell::ServerFireBullet_Implementation()
{
}

void AMaxwell::ToggleAimDown()
{
}

void AMaxwell::ServerToggleAimDown_Implementation()
{
}

void AMaxwell::ShadowShift()
{
}

void AMaxwell::ServerShadowShift_Implementation()
{
}
