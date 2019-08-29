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
	StaticMesh->SetCollisionProfileName(TEXT("BlockAll"));
	StaticMesh->SetWorldScale3D(FVector(1, 1, 5));
	StaticMesh->SetupAttachment(RootComponent);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(StaticMesh);
	Arrow->SetRelativeLocation(FVector::ZeroVector);

	RootComponent = StaticMesh;

	bReplicates = true;
}

void ARitualShrine::BeginPlay()
{
	Super::BeginPlay();
}



// Called every frame
void ARitualShrine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (Acolytes.Num() == 0)
	//{
	//	Destroy();
	//}
}

void ARitualShrine::SpawnAcolytes(int32 Count)
{

	//Remove all acolytes
	for (ARitualAcolyte* Acolyte: Acolytes)
	{
		Acolyte->Destroy();
	}
	Acolytes.Empty(Count);

	//Spawn Acolytes around shrine.
	const float Distance = 200.f;
	float Angle = 0.f;
	for (int i = 0; i < Count; i++)
	{
		//find spawn position
		FVector Location(cos(Angle) * Distance, sin(Angle) * Distance, -25);


		Location = GetTransform().TransformPosition(Location);
		ARitualAcolyte* Acolyte = GetWorld()->SpawnActor<ARitualAcolyte>(Location, FRotator::ZeroRotator);
		Acolyte->AddActorLocalOffset(FVector(0, 0, -100), true);
		Acolyte->SetParentShrine(this);
		Acolytes.Push(Acolyte);
		Angle += (1.f / Count) * 2 * PI ;
	}
}

void ARitualShrine::RemoveAcolyte(ARitualAcolyte* Acolyte)
{
	Acolytes.Remove(Acolyte);
}
