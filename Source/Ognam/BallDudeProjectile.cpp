// Fill out your copyright notice in the Description page of Project Settings.

#include "BallDudeProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "ConstructorHelpers.h"
// Sets default values
ABallDudeProjectile::ABallDudeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set bullet property
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Ball->SetupAttachment(RootComponent);
	Ball->SetWorldScale3D(FVector(0.5));
	Ball->SetStaticMesh(Sphere.Object);
	Ball->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Ball->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Ball->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
	Ball->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	Ball->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	Ball->OnComponentBeginOverlap.AddDynamic(this, &ABallDudeProjectile::StartOverlap);

	RootComponent = Ball;
}

// Called when the game starts or when spawned
void ABallDudeProjectile::BeginPlay()
{
	Super::BeginPlay();
	LifeTime = 0;
	LifeSpan = 3;
}

// Called every frame
void ABallDudeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float ElapsedTime = DeltaTime;
	LifeTime += ElapsedTime;

	//if time has passed, check only till the time it should die.
	if (LifeSpan < LifeTime)
		ElapsedTime -= LifeTime - LifeSpan;

	//Calculate its next position and set position
	FVector Position = InitialPosition + InitialVelocity * LifeTime + Acceleration * LifeTime * LifeTime / 2;
	FHitResult HitResult;
	SetActorLocation(Position, true, &HitResult);
	
	//kill if lived too long.
	if (HitResult.bBlockingHit || LifeSpan < LifeTime)
		Destroy();
}

void ABallDudeProjectile::SetInitialPosition(FVector Value)
{
	InitialPosition = Value;
}

void ABallDudeProjectile::SetInitialVelocity(FVector Value)
{
	InitialVelocity = Value;
}

void ABallDudeProjectile::SetAcceleration(FVector Value)
{
	Acceleration = Value;
}

void ABallDudeProjectile::SetController(AController* Controller)
{
	ParentController = Controller;
}

void ABallDudeProjectile::StartOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ParentController == nullptr || OtherActor == ParentController->GetPawn())
		return;
	UGameplayStatics::ApplyDamage(OtherActor, 34, ParentController, ParentController->GetPawn(), nullptr);
	Destroy();
}

