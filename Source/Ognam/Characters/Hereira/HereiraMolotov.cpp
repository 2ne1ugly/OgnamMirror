// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraMolotov.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ConstructorHelpers.h"
#include "HereiraMolotovEmber.h"

AHereiraMolotov::AHereiraMolotov()
{
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);
	Collision->SetSphereRadius(17.f);
	RootComponent = Collision;

	ConstructorHelpers::FObjectFinder<UStaticMesh> Cylinder(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetStaticMesh(Cylinder.Object);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetWorldScale3D(FVector(0.25f, 0.25f, 0.25f));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeLocation(FVector::ZeroVector);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInterpMovement = true;
	Movement->bSweepCollision = true;
	Movement->bShouldBounce = false;
	Movement->InitialSpeed = 2000.f;
	Movement->ProjectileGravityScale = 1.5f;
	Movement->OnProjectileStop.AddDynamic(this, &AHereiraMolotov::ProjectileStop);
}

void AHereiraMolotov::ProjectileStop(const FHitResult& ImpactResult)
{
	if (HasAuthority())
	{
		FActorSpawnParameters SpawnParam;
		SpawnParam.bNoFail = true;
		SpawnParam.Instigator = Instigator;
		for (int i = 0; i < 32; i++)
		{
			const float Theta = FMath::Min(FMath::Acos(FMath::Sqrt(FMath::FRand())), HALF_PI - DELTA);
			const float Phi = 2.0f * (float)PI * FMath::FRand();
			const float SinTheta = FMath::Sin(Theta);
			FVector Direction(FMath::Cos(Theta), FMath::Cos(Phi) * SinTheta, FMath::Sin(Phi) * SinTheta);
			FRotator Rotator = ImpactResult.ImpactNormal.Rotation().RotateVector(Direction).Rotation();

			AHereiraMolotovEmber* Ember = GetWorld()->SpawnActor<AHereiraMolotovEmber>(GetActorLocation(), Rotator, SpawnParam);
			Ember->SetReplicates(true);
		}
	}
	Destroy();
}

void AHereiraMolotov::BeginPlay()
{
	Super::BeginPlay();

	Collision->MoveIgnoreActors.Add(Instigator);
}

