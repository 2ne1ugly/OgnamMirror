// Fill out your copyright notice in the Description page of Project Settings.

#include "Hereira.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "HereiraArrow.h"
#include "HereiraExplosiveArrow.h"
#include "ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "HereiraSprint.h"

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

void AHereira::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Run sprint cd when finished
	if (CurrentSprint && !CurrentSprint->IsActive())
	{
		CurrentSprint = nullptr;
		GetWorldTimerManager().SetTimer(SprintCooldown, 8.f, false);
	}
}

void AHereira::FireArrow()
{
	if (GetWorldTimerManager().IsTimerActive(BasicReload) || CurrentSprint != nullptr)
	{
		return;
	}
	ServerFireArrow();
	GetWorldTimerManager().SetTimer(BasicReload, 1.5f, false);
}

void AHereira::ServerFireArrow_Implementation() 
{
	if (GetWorldTimerManager().IsTimerActive(BasicReload) || CurrentSprint != nullptr)
	{
		return;
	}
	float Gravity = 1000.f;
	float UpRatio = 0.1f;
	FVector Direction = Camera->GetForwardVector()* (1 - UpRatio) + FVector::UpVector * UpRatio;
	Direction.GetSafeNormal();
	FRotator Rotator = FRotationMatrix::MakeFromX(Direction).Rotator();

	//Set Spawner
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = this;

	AHereiraArrow* Arrow;
	if (bIsExplosiveShot)
	{
		Arrow = GetWorld()->SpawnActor<AHereiraExplosiveArrow>(GetActorLocation(), Rotator, SpawnParameters);
		bIsExplosiveShot = false;
	}
	else
	{
		Arrow = GetWorld()->SpawnActor<AHereiraArrow>(GetActorLocation(), Rotator, SpawnParameters);
	}
	Arrow->SetReplicates(true);
	Arrow->SetInitialPosition(GetActorLocation());
	Arrow->SetInitialVelocity(Direction * 5000);
	Arrow->SetGravity(Gravity);
	GetWorldTimerManager().SetTimer(BasicReload, 1.5f, false);
}

void AHereira::StartSprint()
{
	if (GetWorldTimerManager().IsTimerActive(SprintCooldown) || CurrentSprint != nullptr)
	{
		return;
	}
	ServerStartSprint();
}

void AHereira::ServerStartSprint_Implementation()
{
	//Check Cooldown or In use
	if (GetWorldTimerManager().IsTimerActive(SprintCooldown) || CurrentSprint != nullptr)
	{
		return;
	}
	ApplySprint();
}

void AHereira::ApplySprint_Implementation()
{
	CurrentSprint = NewObject<UHereiraSprint>(this);
	ApplyModifier(CurrentSprint);
}

void AHereira::StopSprint()
{
	if (CurrentSprint == nullptr)
	{
		return;
	}
	ServerStopSprint();
}

void AHereira::ServerStopSprint_Implementation()
{
	if (CurrentSprint == nullptr)
	{
		return;
	}
	InterruptSprint();
}

void AHereira::InterruptSprint_Implementation()
{
	if (CurrentSprint == nullptr)
	{
		return;
	}
	CurrentSprint->Interrupt();
}

void AHereira::LoadExplosiveShot()
{
	if (GetWorldTimerManager().IsTimerActive(ExplosiveShotCooldown))
	{
		return;
	}
	ServerLoadExplosiveShot();
}

void AHereira::ServerLoadExplosiveShot_Implementation()
{
	if (GetWorldTimerManager().IsTimerActive(ExplosiveShotCooldown))
	{
		return;
	}
	GetWorldTimerManager().SetTimer(ExplosiveShotCooldown, 15.f, false);
	GetWorldTimerManager().SetTimer(BasicReload, 0.5f, false);
	bIsExplosiveShot = true;
}
