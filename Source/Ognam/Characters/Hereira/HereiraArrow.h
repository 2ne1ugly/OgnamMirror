// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HereiraArrow.generated.h"

UCLASS()
class OGNAM_API AHereiraArrow : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* Collision;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UProjectileMovementComponent* Movement;

public:	
	AHereiraArrow();

	/*
	**	Binded Functions
	*/
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void ProjectileStop(const FHitResult& ImpactResult);

protected:
	/*
	**	Internal Functions
	*/
	virtual void EndLifeSpan();
	virtual void OnCharacterHit(class AOgnamCharacter* OtherCharacter, const FHitResult& SweepResult);

	/*
	**	Props
	*/
	FTimerHandle LifeSpan;
	float BaseDamage;
	UPROPERTY(EditAnywhere)
	float GravityScale;
};
