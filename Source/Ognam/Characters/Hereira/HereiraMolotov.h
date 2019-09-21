// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HereiraMolotov.generated.h"

UCLASS()
class OGNAM_API AHereiraMolotov : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* Movement;

public:	
	AHereiraMolotov();

protected:
	UFUNCTION()
	void ProjectileStop(const FHitResult& ImpactResult);

	virtual void BeginPlay() override;

};
