// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallDudeProjectile.generated.h"
UCLASS()
class OGNAM_API ABallDudeProjectile : public AActor
{
	GENERATED_BODY()

protected:
	/*
	**	Components
	*/
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Ball;
public:	
	ABallDudeProjectile();

	/*
	**	Binded Function
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	void SetInitialPosition(FVector Value);

	UFUNCTION(BlueprintCallable)
	void SetInitialVelocity(FVector Value);

	UFUNCTION(BlueprintCallable)
	void SetAcceleration(FVector Value);

	UFUNCTION(BlueprintCallable)
	void SetController(class AController* Controller);

protected:
	/*
	**	Internal Functions
	*/
	UFUNCTION()
	void StartOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere)
	class AController* ParentController;

	float LifeTime;
	float LifeSpan;
	FVector InitialPosition;
	FVector InitialVelocity;
	FVector Acceleration;
};
