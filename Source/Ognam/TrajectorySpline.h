// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrajectorySpline.generated.h"

UCLASS()
class OGNAM_API ATrajectorySpline : public AActor
{
	GENERATED_BODY()

protected:

	/*
	**	Components
	*/
	UPROPERTY(VisibleAnywhere)
	class USplineComponent* Spline;

	UPROPERTY(VisibleAnywhere)
	class UBillboardComponent* Billboard;

	UPROPERTY(VisibleAnywhere)
	TArray<class UStaticMeshComponent*> Meshs;

public:	
	// Sets default values for this actor's properties
	ATrajectorySpline();

	/*
	**	Binded Functions
	*/
	virtual void Tick(float DeltaTime) override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	void SetShouldUpdate(bool Value);

	UFUNCTION(BlueprintCallable)
	bool GetShouldUpdate();

	/*
	**	Exported Props
	*/
	UPROPERTY(EditAnywhere)
	TArray<FVector> SplinePoints;

	/*
	**	Exported Functions
	*/
	void SetVisibility(bool Value);

protected:

	/*
	**	Props
	*/
	UPROPERTY(EditAnywhere)
	bool bShouldUpdate;
};
