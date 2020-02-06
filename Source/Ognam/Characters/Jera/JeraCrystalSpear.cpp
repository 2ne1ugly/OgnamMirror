// Fill out your copyright notice in the Description page of Project Settings.


#include "JeraCrystalSpear.h"
#include "Components/BoxComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Ognam/OgnamMacro.h"
#include "Ognam/OgnamStatics.h"
#include "Ognam/OgnamEnum.h"

AJeraCrystalSpear::AJeraCrystalSpear()
{
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetBoxExtent(FVector(70.f, 10.f, 10.f));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);
	RootComponent = Collision;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ArrowObj(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetStaticMesh(ArrowObj.Object);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetRelativeScale3D(FVector(.2f, .2f, 1.4f));
	Mesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator(-90.f, 0.f, 0.f));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInterpMovement = true;
	Movement->bRotationFollowsVelocity = true;
	Movement->bSweepCollision = true;
	Movement->bShouldBounce = false;
	Movement->InitialSpeed = 6000.f;
	Movement->ProjectileGravityScale = 0.f;
	Movement->OnProjectileStop.AddDynamic(this, &AJeraCrystalSpear::ProjectileStop);

	InitialLifeSpan = 5.f;

	BaseDamage = 60.f;
}

void AJeraCrystalSpear::BeginPlay()
{
	Super::BeginPlay();

	Collision->MoveIgnoreActors.Add(GetInstigator());
}

void AJeraCrystalSpear::ProjectileStop(const FHitResult& ImpactResult)
{
	Destroy();

	if (!HasAuthority())
	{
		return;
	}

	IKillable* Killable = Cast<IKillable>(ImpactResult.GetActor());
	if (Killable)
	{
		if (UOgnamStatics::CanDamage(GetWorld(), GetInstigator(), Killable, EDamageMethod::DamagesEnemy))
		{
			AActor* Reciever = Cast<AActor>(Killable);
			UGameplayStatics::ApplyPointDamage(Reciever, BaseDamage, ImpactResult.ImpactNormal, ImpactResult, GetInstigatorController(), this, nullptr);
		}
	}
	
}
