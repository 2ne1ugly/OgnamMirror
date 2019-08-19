// Fill out your copyright notice in the Description page of Project Settings.


#include "BallDude.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/InputComponent.h"
#include "Animation/AnimBlueprint.h"
#include "Camera/CameraComponent.h"
#include "BallDudeProjectile.h"

ABallDude::ABallDude()
{
	//Default mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkMesh(TEXT("SkeletalMesh'/Game/Animation/BallDude.BallDude'"));
	GetMesh()->SetSkeletalMesh(SkMesh.Object);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	NumBalls = 0;
	MaxNumBalls = 3;
	ChargeTime = 0;
	ChargeTimePerBall = 2;
	BallRotationSpeed = 100;

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
		Balls.Push(StaticMeshComponent);
		Angle += (PI * 2) / MaxNumBalls;
	}
} 

void ABallDude::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChargeTime += DeltaTime;
	if (NumBalls >= MaxNumBalls)
	{
		ChargeTime = 0;
	}
	if (ChargeTime >= ChargeTimePerBall)
	{
		ChargeTime -= ChargeTimePerBall;
		NumBalls++;
	}
	BallSpinner->AddLocalRotation(FRotator(0, DeltaTime * BallRotationSpeed, 0));
}

void ABallDude::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABallDude::ThrowLeft);
}

void ABallDude::ThrowLeft()
{
	ServerThrowLeft();
}

void ABallDude::ServerThrowLeft_Implementation()
{
	MultiCastThrowLeft();
}

void ABallDude::MultiCastThrowLeft_Implementation()
{
	ABallDudeProjectile* Projectile = GetWorld()->SpawnActor<ABallDudeProjectile>(GetActorLocation(), FRotator::ZeroRotator);
	Projectile->SetAcceleration(Camera->GetComponentTransform().TransformVector(FVector(0, 1, -1) * 2000));
	Projectile->SetInitialVelocity(Camera->GetComponentTransform().TransformVector(FVector(6, -1, 1) * 500));
	Projectile->SetInitialPosition(GetActorLocation());
	Projectile->SetController(GetController());
}

