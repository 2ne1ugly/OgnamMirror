// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OgnamProjectile.generated.h"

UCLASS()	
class OGNAM_API AOgnamProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Bullet;

	UPROPERTY(EditAnywhere)
	class UNiagaraComponent* Trail;

	UPROPERTY()
	class AController* ParentController;
public:	
	// Sets default values for this actor's properties
	AOgnamProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetInitialDirection(FVector Direction);
	void SetController(class AController* Controller);
private:
	float	LifeTime;
	float	LifeSpan;
	float	Speed;
	FVector	InitialDirection;
};
