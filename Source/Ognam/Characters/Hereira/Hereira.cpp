// Fill out your copyright notice in the Description page of Project Settings.

#include "Hereira.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "HereiraSprint.h"
#include "HereiraExplosiveArrowReady.h"
#include "HereiraCanFastReload.h"
#include "UnrealNetwork.h"

AHereira::AHereira()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDFinder(TEXT("/Game/UI/CharacterHUD/HereiraHUD"));
	if (HUDFinder.Succeeded())
	{
		CharacterSpecificHUDClass = HUDFinder.Class;
	}
	MaxArrows = 2;
	NumArrows = MaxArrows;
}

void AHereira::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Basic"), IE_Pressed, this, &AHereira::FireArrow);
	PlayerInputComponent->BindAction(TEXT("Mobility"), IE_Pressed, this, &AHereira::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Mobility"), IE_Released, this, &AHereira::StopSprint);
	PlayerInputComponent->BindAction(TEXT("Unique"), IE_Pressed, this, &AHereira::LoadExplosiveShot);
	PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &AHereira::Reload);
}

void AHereira::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void AHereira::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHereira::FireArrow()
{
	if (NumArrows <= 0 || GetWorldTimerManager().IsTimerActive(BasicDelay) || GetModifier<UHereiraSprint>())
	{
		return;
	}
	NumArrows--;
	GetWorldTimerManager().SetTimer(BasicDelay, 0.1f, false);
	ServerFireArrow();
	if (NumArrows == 0)
	{
		Reload();
	}
}

void AHereira::ServerFireArrow_Implementation() 
{
	if (NumArrows <= 0 || GetWorldTimerManager().IsTimerActive(BasicDelay) || GetModifier<UHereiraSprint>())
	{
		return;
	}
	NumArrows--;

	float UpRatio = 0.1f;
	FVector Direction = Camera->GetForwardVector()* (1 - UpRatio) + FVector::UpVector * UpRatio;
	Direction.GetSafeNormal();
	FRotator Rotator = FRotationMatrix::MakeFromX(Direction).Rotator();

	//Set Spawner
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoFail = true;
	SpawnParameters.Instigator = this;


	UHereiraExplosiveArrowReady* ExplosiveReady = GetModifier<UHereiraExplosiveArrowReady>();
	FVector Location = GetActorLocation() + FVector(0.f, 0.f, 60.f);

	AHereiraArrow* Arrow;
	if (ExplosiveReady && ExplosiveReady->Use())
	{
		Arrow = GetWorld()->SpawnActor<AHereiraExplosiveArrow>(Location, Rotator, SpawnParameters);
		GetWorldTimerManager().SetTimer(ExplosiveShotCooldown, 5.f, false);
		ClientFiredExplosiveShot();
	}
	else
	{
		Arrow = GetWorld()->SpawnActor<AHereiraArrow>(Location, Rotator, SpawnParameters);
	}
	Arrow->SetReplicates(true);
	GetWorldTimerManager().SetTimer(BasicDelay, 0.1f, false);
	if (NumArrows <= 0)
	{
		Reload();
	}
}

void AHereira::StartSprint()
{
	if (GetWorldTimerManager().IsTimerActive(SprintCooldown) || GetModifier<UHereiraSprint>())
	{
		return;
	}
	ServerStartSprint();
}

void AHereira::ServerStartSprint_Implementation()
{
	//Check Cooldown or In use
	if (GetWorldTimerManager().IsTimerActive(SprintCooldown) || GetModifier<UHereiraSprint>())
	{
		//UE_LOG(LogNet, Warning, TEXT("%s Mismatch!"), __FUNCTIONW__);
		return;
	}
	NetApplyDefaultModifier(UHereiraSprint::StaticClass());
}

void AHereira::StopSprint()
{
	if (!GetModifier<UHereiraSprint>())
	{
		return;
	}
	ServerStopSprint();
}

void AHereira::ServerStopSprint_Implementation()
{
	if (!GetModifier<UHereiraSprint>())
	{
		//UE_LOG(LogNet, Warning, TEXT("%s Mismatch!"), __FUNCTIONW__);
		return;
	}
	EndSprint();
}

void AHereira::EndSprint_Implementation()
{
	GetWorldTimerManager().SetTimer(SprintCooldown, 6.f, false);
	UHereiraSprint* HereiraSprint = GetModifier<UHereiraSprint>();
	if (!HereiraSprint)
	{
		return;
	}
	HereiraSprint->Interrupt();
}

void AHereira::LoadExplosiveShot()
{
	if (GetWorldTimerManager().IsTimerActive(ExplosiveShotCooldown) ||
		GetModifier<UHereiraExplosiveArrowReady>() != nullptr)
	{
		return;
	}
	ServerLoadExplosiveShot();
}

void AHereira::ServerLoadExplosiveShot_Implementation()
{
	if (GetWorldTimerManager().IsTimerActive(ExplosiveShotCooldown) ||
		GetModifier<UHereiraExplosiveArrowReady>() != nullptr)
	{
		//UE_LOG(LogNet, Warning, TEXT("%s Mismatch!"), __FUNCTIONW__);
		return;
	}
	NetApplyDefaultModifier(UHereiraExplosiveArrowReady::StaticClass());
}

void AHereira::ClientFiredExplosiveShot_Implementation()
{
	UHereiraExplosiveArrowReady* Arrow = GetModifier<UHereiraExplosiveArrowReady>();
	if (Arrow)
	{
		Arrow->Use();
	}
	GetWorldTimerManager().SetTimer(ExplosiveShotCooldown, 5.f, false);
}

void AHereira::Reload()
{
	UHereiraCanFastReload* FastReload = GetModifier<UHereiraCanFastReload>();
	if (FastReload && FastReload->Use())
	{
		GetWorldTimerManager().SetTimer(BasicReload, this, &AHereira::FinishReload, 1.f, false);
	}
	else
	{
		GetWorldTimerManager().SetTimer(BasicReload, this, &AHereira::FinishReload, 1.5f, false);
	}
}

void AHereira::FinishReload()
{
	NumArrows = MaxArrows;
}

