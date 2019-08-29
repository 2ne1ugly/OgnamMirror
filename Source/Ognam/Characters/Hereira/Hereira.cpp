// Fill out your copyright notice in the Description page of Project Settings.

#include "Hereira.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "HereiraArrow.h"
#include "ConstructorHelpers.h"

AHereira::AHereira()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDFinder(TEXT("/Game/UI/CharacterHUD/HereiraHUD"));
	if (HUDFinder.Succeeded())
	{
		CharacterSpecificHUDClass = HUDFinder.Class;
	}
}

void AHereira::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Basic"), IE_Pressed, this, &AHereira::FireArrow);
	PlayerInputComponent->BindAction(TEXT("Mobility"), IE_Pressed, this, &AHereira::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Mobility"), IE_Released, this, &AHereira::StopSprint);
	PlayerInputComponent->BindAction(TEXT("Unique"), IE_Pressed, this, &AHereira::LoadExplosiveShot);
}

void AHereira::FireArrow()
{
	if (GetWorldTimerManager().IsTimerActive(BasicReload) || GetWorldTimerManager().IsTimerActive(SprintDuration))
	{
		return;
	}
	ServerFireArrow();
	GetWorldTimerManager().SetTimer(BasicReload, 1.5f, false);
}

void AHereira::ServerFireArrow_Implementation() 
{
	if (GetWorldTimerManager().IsTimerActive(BasicReload) || GetWorldTimerManager().IsTimerActive(SprintDuration))
	{
		return;
	}
	float Gravity = 1000.f;
	float UpRatio = 0.1f;
	FVector Direction = Camera->GetForwardVector()* (1 - UpRatio) + FVector::UpVector * UpRatio;
	Direction.GetSafeNormal();
	FRotator Rotator = FRotationMatrix::MakeFromX(Direction).Rotator();
	AHereiraArrow* Arrow = GetWorld()->SpawnActor<AHereiraArrow>(GetActorLocation(), Rotator);
	Arrow->SetReplicates(true);
	Arrow->SetInitialPosition(GetActorLocation());
	Arrow->SetInitialVelocity(Direction * 5000);
	Arrow->SetGravity(Gravity);
	Arrow->SetController(GetController<APlayerController>());
	GetWorldTimerManager().SetTimer(BasicReload, 1.5f, false);
}

void AHereira::StartSprint()
{
	if (GetWorldTimerManager().IsTimerActive(SprintCooldown) ||
		GetWorldTimerManager().IsTimerActive(SprintDuration))
	{
		return;
	}
	ServerStartSprint();
	ServerStartSprint_Implementation();
}

void AHereira::ServerStartSprint_Implementation()
{
	//Check Cooldown or In use
	if (GetWorldTimerManager().IsTimerActive(SprintCooldown) ||
		GetWorldTimerManager().IsTimerActive(SprintDuration))
	{
		return;
	}
	GetWorldTimerManager().SetTimer(SprintDuration, this, &AHereira::EndSprint, 3.f, false);
	GetCharacterMovement()->MaxWalkSpeed = 600 * 2;
}

void AHereira::StopSprint()
{
	//Check In use
	if (!GetWorldTimerManager().IsTimerActive(SprintDuration))
	{
		return;
	}
	ServerStopSprint();
	ServerStopSprint_Implementation();
}

void AHereira::ServerStopSprint_Implementation()
{
	if (!GetWorldTimerManager().IsTimerActive(SprintDuration))
	{
		return;
	}
	GetWorldTimerManager().ClearTimer(SprintDuration);
	GetWorldTimerManager().SetTimer(SprintCooldown, 8.f, false);
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AHereira::EndSprint()
{
	if (GetWorldTimerManager().IsTimerActive(SprintCooldown))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s SprintCooldown pending when duration ended!"), __FUNCTION__);
		return;
	}
	GetWorldTimerManager().SetTimer(SprintCooldown, 8.f, false);
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AHereira::LoadExplosiveShot()
{
}
