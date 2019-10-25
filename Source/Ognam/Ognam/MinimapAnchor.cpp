// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "MinimapAnchor.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

AMinimapAnchor::AMinimapAnchor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("StaticMesh'/Game/Meshes/MinimapAnchor.MinimapAnchor'"));

	AnchorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Anchor Mesh"));
	RootComponent = AnchorMesh;
	AnchorMesh->SetStaticMesh(Mesh.Object);
	//AnchorMesh->bHiddenInGame = true;
	AnchorMesh->SetWorldRotation(FRotator(0.f, 0.f, 90.f));
}

void AMinimapAnchor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMinimapAnchor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector2D AMinimapAnchor::FindScaledOffset(AActor* FromActor)
{
	FVector2D Res = FVector2D(FromActor->GetActorLocation()) + Offset;
	return (Res * Scale);
}


