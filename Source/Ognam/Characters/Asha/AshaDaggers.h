// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AshaDaggers.generated.h"

UCLASS()
class OGNAM_API AAshaDaggers : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* Collision;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* Movement;

public:	
	// Sets default values for this actor's properties
	AAshaDaggers();

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void ProjectileStop(const FHitResult& ImpactResult);

	/*
	**	Props
	*/
	float BaseDamage;
};
