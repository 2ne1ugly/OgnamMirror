// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OgnamProjectile.generated.h"

UCLASS()	
class OGNAM_API AOgnamProjectile : public AActor
{
	GENERATED_BODY()

protected:
	/*
	**	Components
	*/
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Bullet;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* Trail;

public:	
	AOgnamProjectile();

	/*
	**	Binded Functions
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	void SetInitialDirection(FVector Direction);

	UFUNCTION(BlueprintCallable)
	void SetController(class AController* Controller);

private:
	/*
	**	Props
	*/
	UPROPERTY()
	class AController* ParentController;
	float LifeTime;
	float LifeSpan;
	float Speed;
	FVector	InitialDirection;
};
