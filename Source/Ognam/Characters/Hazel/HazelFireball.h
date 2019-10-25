// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HazelFireball.generated.h"

UCLASS()
class OGNAM_API AHazelFireball : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	class USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* Movement;

public:
	AHazelFireball();

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void ProjectileStop(const FHitResult& ImpactResult);
	/*
	**	Props
	*/
	float BaseDamage;
};
