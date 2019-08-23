// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RitualShrine.generated.h"

UCLASS()
class OGNAM_API ARitualShrine : public AActor
{
	GENERATED_BODY()

	/*
	**	Components
	*/
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	class UArrowComponent* Arrow;

public:	
	ARitualShrine();

	/*
	**	Binded Function
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	/*
	**	Internal Function
	*/
	UFUNCTION(NetMulticast, Reliable)
	void SpawnAcolytes(int32 Count);
	void SpawnAcolytes_Implementation(int32 Count);

	/*
	**	Props
	*/
	UPROPERTY()
	TArray<class ARitualAcolyte*> Acolytes;
};
