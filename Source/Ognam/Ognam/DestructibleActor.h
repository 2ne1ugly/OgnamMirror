// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleActor.generated.h"

UCLASS()
class OGNAM_API ADestructibleActor : public AActor
{
	GENERATED_BODY()

protected:
	/*
	**	Components
	*/
	UPROPERTY(EditAnywhere)
	class UPrimitiveComponent* Collision;

	UPROPERTY(EditAnywhere)
	class UFieldSystemComponent* DestructionField;

	UPROPERTY(EditAnywhere)
	class UGeometryCollectionComponent* GeometryCollection;

public:	
	ADestructibleActor();

	virtual void BeginPlay() override;

	virtual void Destruct();

protected:
	/*
	**	Props
	*/
	UPROPERTY(EditAnywhere)
	float Health;

	UPROPERTY(VisibleAnywhere)
	bool bDestructed;

	FTimerHandle DestructTimer;
};
