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
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	Bullet->SetupAttachment(RootComponent);
	Bullet->SetWorldScale3D(FVector(0.1));
	Bullet->SetStaticMesh(Sphere.Object);
	Bullet->SetCollisionProfileName(TEXT("BlockAll"));
	Bullet->SetVisibility(true);

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

	//Trail->Activate();
	//SetActorLocation(FVector(0, 0, 100));
}

// Called every frame
void AOgnamProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LifeTime += DeltaTime;
	if (LifeSpan < LifeTime)
		Destroy();
	FHitResult HitResult;
	SetActorLocation(GetActorLocation() + DeltaTime * InitialDirection * Speed, true, &HitResult);
	if (HitResult.bBlockingHit)
	{
		if (HitResult.Actor.IsValid())
		{
			UGameplayStatics::ApplyPointDamage(HitResult.Actor.Get(), 30, InitialDirection, HitResult, Controller, this, nullptr);
		}
		Destroy();
	}
	/*not working*/
}

void AOgnamProjectile::SetInitialDirection(FVector Direction)
{
	InitialDirection = Direction;
}

void AOgnamProjectile::SetController(AController* Controller)
{
	Controller = Controller;
}

