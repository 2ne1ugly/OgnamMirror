// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "RitualSpectator.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Ognam/OgnamMacro.h"
#include "RitualPlayerState.h"

ARitualSpectator::ARitualSpectator()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComponent->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	RootComponent = CapsuleComponent;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SocketOffset = FVector(0.f, 0.f, 120.f);
	SpringArm->SetRelativeRotation(FRotator(-30.f, 0.f, 0.f));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	index = 0;
}

void ARitualSpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("CameraYaw", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("CameraPitch", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Basic", IE_Pressed, this, &ARitualSpectator::PrevPlayerPressed);
	PlayerInputComponent->BindAction("Sub", IE_Pressed, this, &ARitualSpectator::NextPlayerPressed);
}

void ARitualSpectator::NextPlayerPressed()
{
	FindAlivePlayerStates();
	if (AlivePlayerStates.Num() == 0)
	{
		O_LOG(TEXT("None is alive"));
		return;
	}

	index++;
	if (index >= AlivePlayerStates.Num())
	{
		index = 0;
	}
	ServerGetPlayerStatePawn(AlivePlayerStates[index]);
}

void ARitualSpectator::PrevPlayerPressed()
{
	FindAlivePlayerStates();
	if (AlivePlayerStates.Num() == 0)
	{
		O_LOG(TEXT("None is alive"));
		return;
	}

	index--;
	if (index < 0)
	{
		index = AlivePlayerStates.Num() - 1;
	}
	ServerGetPlayerStatePawn(AlivePlayerStates[index]);
}

void ARitualSpectator::ServerGetPlayerStatePawn_Implementation(APlayerState* TargetPlayerState)
{
	ClientRecievePawn(TargetPlayerState->GetPawn());
}

void ARitualSpectator::ClientRecievePawn_Implementation(APawn* Pawn)
{
	if (!Pawn)
	{
		O_LOG(TEXT("No Pawn!"));
		return;
	}
	CapsuleComponent->AttachToComponent(Pawn->GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	CapsuleComponent->SetRelativeLocation(FVector(0.f));
	CapsuleComponent->SetAbsolute(false, true, true);
}

void ARitualSpectator::FindAlivePlayerStates()
{
	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (!GameState)
	{
		O_LOG(TEXT("GameState not here"));
		return;
	}
	if (GameState->PlayerArray.Num() == 0)
	{
		O_LOG(TEXT("No Players in player array"));
		return;
	}
	AlivePlayerStates.Empty();
	for (APlayerState* TargetPlayerState: GameState->PlayerArray)
	{
		ARitualPlayerState* RitualPlayerState = Cast<ARitualPlayerState>(TargetPlayerState);
		if (RitualPlayerState->IsAlive())
		{
			AlivePlayerStates.Push(RitualPlayerState);
		}
	}
}

