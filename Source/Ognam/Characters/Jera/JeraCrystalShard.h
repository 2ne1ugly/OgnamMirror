// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JeraCrystalShard.generated.h"

UCLASS()
class OGNAM_API AJeraCrystalShard : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UBoxComponent* Collision;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* Movement;

public:	
	AJeraCrystalShard();

	virtual void BeginPlay() override;
};
