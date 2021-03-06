// Fill out your copyright notice in the Description page of Project Settings.


#include "AshaDaggers.h"
#include "Components/SphereComponent.h"
#include "ConstructorHelpers.h"
#include "AshaDaggersImpact.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Ognam/OgnamMacro.h"
#include "Ognam/OgnamStatics.h"
#include "Ognam/OgnamEnum.h"

// Sets default values
AAshaDaggers::AAshaDaggers()
{
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetBoxExtent(FVector(50.f, 10.f, 10.f));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECR_Block);
	Collision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Block);
	RootComponent = Collision;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DaggerMeshCH(TEXT("StaticMesh'/Game/Meshes/Asha_knife_basic.Asha_knife_basic'"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetStaticMesh(DaggerMeshCH.Object);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	Mesh->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator(0.f, 0.f, 0.f));

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->bInterpMovement = true;
	Movement->bRotationFollowsVelocity = true;
	Movement->bSweepCollision = true;
	Movement->bShouldBounce = false;
	Movement->InitialSpeed = 8000.f;
	Movement->ProjectileGravityScale = 0.7f;
	Movement->OnProjectileStop.AddDynamic(this, &AAshaDaggers::ProjectileStop);

	InitialLifeSpan = 5.f;

	BaseDamage = 25.f;
}

void AAshaDaggers::BeginPlay()
{
	Super::BeginPlay();
	Collision->MoveIgnoreActors.Add(GetInstigator());
}

void AAshaDaggers::ProjectileStop(const FHitResult& ImpactResult)
{
	Destroy();
	if (!HasAuthority())
	{
		return;
	}
	FVector ImpactLocation = ImpactResult.ImpactPoint;
	NetPlayFeedback_Implementation(ImpactLocation);
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

void AAshaDaggers::NetPlayFeedback_Implementation(FVector ImpactLocation)
{
	AAshaDaggersImpact* Impact = GetWorld()->SpawnActor<AAshaDaggersImpact>(ImpactLocation, FRotator::ZeroRotator);
}



