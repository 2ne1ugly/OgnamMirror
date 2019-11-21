// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleActor.h"
#include "Components/PrimitiveComponent.h"
#include "FieldSystemComponent.h"
#include "GeometryCollectionComponent.h"
#include "TimerManager.h"
#include "Ognam/OgnamMacro.h"

// Sets default values
ADestructibleActor::ADestructibleActor()
{
	Collision = CreateDefaultSubobject<UPrimitiveComponent>(TEXT("Collision"));
	RootComponent = Collision;
	Collision->SetCollisionProfileName(TEXT("BlockAll"));

	DestructionField = CreateDefaultSubobject<UFieldSystemComponent>(TEXT("Field System"));
	DestructionField->SetupAttachment(RootComponent);
	DestructionField->SetRelativeLocation(FVector::ZeroVector);

	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("Field System"));
	GeometryCollection->SetupAttachment(RootComponent);
	GeometryCollection->SetRelativeLocation(FVector::ZeroVector);
}

void ADestructibleActor::BeginPlay()
{
	Super::BeginPlay();

	//Set Destruction Timer
	GetWorld()->GetTimerManager().SetTimer(DestructTimer, this, &ADestructibleActor::Destruct, 5.f, false);
}

void ADestructibleActor::Destruct()
{
	if (bDestructed)
	{
		O_LOG(TEXT("Destruct Called multiple times"));
		return;
	}
	O_LOG(TEXT("Destruct!"));

	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Destruction field and whatever.
}

