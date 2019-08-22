// Fill out your copyright notice in the Description page of Project Settings.


#include "BallDude.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Animation/AnimBlueprint.h"
#include "Camera/CameraComponent.h"
#include "BallDudeProjectile.h"
#include "TrajectorySpline.h"

ABallDude::ABallDude()
{
	//Default mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkMesh(TEXT("SkeletalMesh'/Game/Animation/BallDude.BallDude'"));
	GetMesh()->SetSkeletalMesh(SkMesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	NumBalls = 0;
	MaxNumBalls = 3;
	BallChargeTime = 0;
	BallChargeTimePerBall = 2;
	BallRotationSpeed = 100;
	ChargeTime = 0;
	bIsCharging = true;

	//Arrow for spin.
	BallSpinner = CreateDefaultSubobject<UArrowComponent>(TEXT("BallSpinner"));
	BallSpinner->SetupAttachment(RootComponent);
	BallSpinner->SetRelativeLocation(FVector::ZeroVector);
	BallSpinner->SetAbsolute(false, true);

	//PreInit balls
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BallMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	float Angle = 0;
	for (int i = 0; i < MaxNumBalls; i++)
	{
		UStaticMeshComponent* StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball_" + i));
		StaticMeshComponent->SetStaticMesh(BallMesh.Object);
		StaticMeshComponent->SetWorldScale3D(FVector(0.25, 0.25, 0.25));
		StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
		StaticMeshComponent->SetRelativeLocation(FVector(FMath::Cos(Angle) * 60, FMath::Sin(Angle) * 60, 0));
		StaticMeshComponent->SetupAttachment(BallSpinner);
		StaticMeshComponent->SetVisibility(false);
		Balls.Push(StaticMeshComponent);
		Angle += (PI * 2) / MaxNumBalls;
	}

	USceneComponent* TrajectoryHost= CreateDefaultSubobject<USceneComponent>("Trajectory");

	//Pre init meshs
	for (int i = 0; i < 27; i++)
	{
		UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(
			*FString::Printf(TEXT("Marker_%d"), i));
		MeshComponent->SetStaticMesh(BallMesh.Object);
		MeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
		MeshComponent->SetWorldScale3D(FVector(0.15));
		MeshComponent->SetupAttachment(TrajectoryHost);
		MeshComponent->SetVisibility(false);
		MeshComponent->bHasMotionBlurVelocityMeshes = false;
		Trajectory.Push(MeshComponent);
	}
	//Trajectory->SetVisibility(false);
} 

void ABallDude::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BallChargeTime += DeltaTime;
	if (NumBalls >= MaxNumBalls)
	{
		BallChargeTime = 0;
	}
	if (BallChargeTime >= BallChargeTimePerBall)
	{
		BallChargeTime -= BallChargeTimePerBall;
		AddBalls();
	}
	BallSpinner->AddLocalRotation(FRotator(0, DeltaTime * BallRotationSpeed, 0));

	if (bIsCharging)
	{
		ChargeTime += DeltaTime;
		if (ChargeTime > 3)
			ChargeTime = 3;
		float Time = 0;
		for (int i = 0; i < Trajectory.Num(); i++)
		{
			Trajectory[i]->SetWorldLocation(CalculateTrajectoryPosition(Time, ChargeTime));
			Time += 1.f / (Trajectory.Num() - 1);
		}
	}
}

void ABallDude::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABallDude::ThrowLeft);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ABallDude::StopThrowLeft);
}

void ABallDude::ThrowLeft()
{
	if (NumBalls <= 0)
		return;
	bIsCharging = true;
	for (int i = 0; i < Trajectory.Num(); i++)
	{
		Trajectory[i]->SetVisibility(true);
	}
}

void ABallDude::StopThrowLeft()
{
	if (!bIsCharging)
		return;
	bIsCharging = false;
	for (int i = 0; i < Trajectory.Num(); i++)
	{
		Trajectory[i]->SetVisibility(false);
	}
	ServerThrowLeft(ChargeTime);
}

void ABallDude::ServerThrowLeft_Implementation(float Charge)
{
	MultiCastThrowLeft(Charge);
}

void ABallDude::MultiCastThrowLeft_Implementation(float Charge)
{
	UseBalls();
	ABallDudeProjectile* Projectile = GetWorld()->SpawnActor<ABallDudeProjectile>(GetActorLocation(), FRotator::ZeroRotator);
	Projectile->SetAcceleration(Camera->GetComponentTransform().TransformVector(FVector(0, 1, -1) * 2000));
	Projectile->SetInitialVelocity(Camera->GetComponentTransform().TransformVector(FVector(6, -1, 1) * 500));
	Projectile->SetInitialPosition(GetActorLocation());
	Projectile->SetController(GetController());
}
void ABallDude::AddBalls()
{
	NumBalls++;
	if (NumBalls >= 1 && NumBalls <= MaxNumBalls)
	{
		Balls[NumBalls - 1]->SetVisibility(true);
	}
}
void ABallDude::UseBalls()
{
	NumBalls--;
	if (NumBalls >= 0 && NumBalls < MaxNumBalls)
	{
		Balls[NumBalls]->SetVisibility(false);
	}
}
FVector ABallDude::CalculateTrajectoryPosition(float Time, float Charge)
{
	FVector Acceleration = Camera->GetComponentTransform().TransformVector(FVector(0, 1, -1) * 2000);
	FVector InitialVelocity = Camera->GetComponentTransform().TransformVector(FVector(6, -1, 1) * 500);
	return GetActorLocation() + InitialVelocity * Time + Acceleration * Time * Time / 2;
}

