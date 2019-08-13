// Fill out your copyright notice in the Description page of Project Settings.


#include "RitualShrine.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "RitualAcolyte.h"

// Sets default values
ARitualShrine::ARitualShrine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetStaticMesh(Mesh.Object);
	StaticMesh->SetMobility(EComponentMobility::Static);
	StaticMesh->SetWorldScale3D(FVector(1, 1, 5));
	StaticMesh->SetupAttachment(RootComponent);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(StaticMesh);
	Arrow->SetRelativeLocation(FVector::ZeroVector);

	RootComponent = StaticMesh;
}

// Called when the game starts or when spawned
void ARitualShrine::BeginPlay()
{
	Super::BeginPlay();

	/*
	** Make sure if there aren't multiple acolytes.
	*/
	SpawnAcolytes(2);
}

// Called every frame
void ARitualShrine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARitualShrine::SpawnAcolytes_Implementation(int32 Count)
{
	//Spawn Acolytes around shrine.

	const float Distance = 100.f;
	float Angle = 0.f;
	for (int i = 0; i < Count; i++)
	{
		//find spawn position
		FVector Location(cos(Angle) * Distance, sin(Angle) * Distance, 0);
		Location = GetTransform().GetLocation() + GetTransform().TransformPosition(Location);

		ARitualAcolyte* Acolyte = GetWorld()->SpawnActor<ARitualAcolyte>(Location, FRotator::ZeroRotator);
		Acolyte->SetParentShrine(this);
		Acolytes.Push(Acolyte);
		Angle += (1.f / Count) * 2 * PI ;
	}
}

