// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "OgnamCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Utility"

// Sets default values
AOgnamProjectile::AOgnamProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set bullet property
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	Bullet->SetupAttachment(RootComponent);
	Bullet->SetWorldScale3D(FVector(0.1));
	Bullet->SetStaticMesh(Sphere.Object);
	Bullet->SetCollisionProfileName(TEXT("BlockAll"));
	Bullet->SetVisibility(true);

	// Set Particle effects, being buggy.
	//static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Niagara(TEXT("NiagaraSystem'/Game/Effect/BulletTrail2.BulletTrail2'"));
	Trail = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Trail"));
	//if (Niagara.Succeeded())
	//	Trail->SetAsset(Niagara.Object);
	Trail->SetupAttachment(Bullet);
	Speed = 10000;

	RootComponent = Bullet;
}

// Called when the game starts or when spawned
void AOgnamProjectile::BeginPlay()
{
	Super::BeginPlay();
	LifeTime = 0;
	LifeSpan = 1;
}

// Called every frame
void AOgnamProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float ElapsedTime = DeltaTime;
	LifeTime += ElapsedTime;

	//if time has passed, check only till the time it should die.
	if (LifeSpan < LifeTime)
		ElapsedTime -= LifeTime - LifeSpan;

	//Calculate Hit registeration.
	FHitResult HitResult;
	SetActorLocation(GetActorLocation() + ElapsedTime * InitialDirection * Speed, true, &HitResult);
	if (HitResult.bBlockingHit)
	{
		if (HitResult.Actor.IsValid())
		{
			UGameplayStatics::ApplyPointDamage(HitResult.Actor.Get(), 30, InitialDirection, HitResult, ParentController, this, nullptr);
		}
		Destroy();
	}

	//kill if lived too long.
	if (LifeSpan < LifeTime)
		Destroy();
}

void AOgnamProjectile::SetInitialDirection(FVector Direction)
{
	InitialDirection = Direction;
}

void AOgnamProjectile::SetController(AController* Controller)
{
	ParentController = Controller;
}

