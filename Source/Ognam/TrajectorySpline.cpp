// Fill out your copyright notice in the Description page of Project Settings.


#include "TrajectorySpline.h"
#include "Components/BillboardComponent.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

ATrajectorySpline::ATrajectorySpline()
{
	PrimaryActorTick.bCanEverTick = true;

	//Create Bilboard to show in viewport
	static ConstructorHelpers::FObjectFinder<UTexture2D> Image(TEXT("Texture2D'/Engine/EditorResources/S_Actor.S_Actor'"));
	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	Billboard->SetSprite(Image.Object);
	RootComponent = Billboard;

	//Create Spline
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(Billboard);

	//Pre init meshs
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	for (int i = 0; i < 9; i++)
	{
		UStaticMeshComponent* MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(
			*FString::Printf(TEXT("Marker_%d"), i));
		MeshComponent->SetStaticMesh(Mesh.Object);
		MeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
		MeshComponent->SetupAttachment(Spline);
		MeshComponent->SetWorldScale3D(FVector(0.1));
		Meshs.Push(MeshComponent);
	}
	bShouldUpdate = true;
	//SplinePoints.Push(FVector(0, 0, 0));
	//SplinePoints.Push(FVector(100, 100, 100));

}

void ATrajectorySpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldUpdate)
	{
		Spline->SetSplinePoints(SplinePoints, ESplineCoordinateSpace::World);
		for (int i = 0; i < Meshs.Num(); i++)
		{
			float CurrentTime = ((float)i) / (Meshs.Num() - 1);
			Meshs[i]->SetWorldLocation(Spline->GetLocationAtTime(CurrentTime, ESplineCoordinateSpace::World));
		}
	}
}

void ATrajectorySpline::SetShouldUpdate(bool Value)
{
	bShouldUpdate = Value;
}

bool ATrajectorySpline::GetShouldUpdate()
{
	return bShouldUpdate;
}

void ATrajectorySpline::SetVisibility(bool Value)
{
	Spline->SetVisibility(Value, true);
}

