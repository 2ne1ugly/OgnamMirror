// Fill out your copyright notice in the Description page of Project Settings.


#include "JeraCrystalShard.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AJeraCrystalShard::AJeraCrystalShard()
{
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetBoxExtent(FVector(40.f, 5.f, 5.f));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);
	RootComponent = Collision;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowObj(TEXT("StaticMesh'/Game/Meshes/Arrow/M_Arrow_Static.M_Arrow_Static'"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetStaticMesh(ArrowObj.Object);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetRelativeScale3D(FVector(0.66, 0.66, .66f));
	Mesh->SetRelativeLocationAndRotation(FVector(-20.f, 0.f, 0.f), FRotator(-90.f, 0.f, 0.f));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInterpMovement = true;
	Movement->bRotationFollowsVelocity = true;
	Movement->bSweepCollision = true;
	Movement->bShouldBounce = false;
	Movement->InitialSpeed = 6000.f;
	Movement->ProjectileGravityScale = 0.f;
	//Movement->OnProjectileStop.AddDynamic(this, &AJeraCrystalSpear::ProjectileStop);

	InitialLifeSpan = 5.f;

	//BaseDamage = 60.f;
}

void AJeraCrystalShard::BeginPlay()
{
	Super::BeginPlay();

	Collision->MoveIgnoreActors.Add(Instigator);
}
