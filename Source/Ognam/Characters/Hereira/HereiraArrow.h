// Fill out your copyright notice in the Description page of Project Settings.

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
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void ProjectileStop(const FHitResult& ImpactResult);

protected:
	/*
	**	Internal Functions
	*/
	virtual void EndLifeSpan();
	virtual void OnCharacterHit(class APawn* OtherCharacter, const FHitResult& SweepResult);
	virtual void OnCharacterHit(class IKillable* OtherCharacter, const FHitResult& SweepResult);

	/*
	**	Props
	*/
	FTimerHandle LifeSpan;
	float BaseDamage;
	UPROPERTY(EditAnywhere)
	float GravityScale;
};
