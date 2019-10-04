// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Queue.h"
#include "BloodhoundThorns.generated.h"

UCLASS()
class OGNAM_API ABloodhoundThorns : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	class UArrowComponent* StartingPoint;

public:	
	ABloodhoundThorns();

	virtual void BeginPlay() override;

protected:
	void SpawnThorn();
	void RemoveThorn();

	/*
	**	Props
	*/
	UPROPERTY(EditAnywhere)
	UStaticMesh* ThornMesh;

	int32 NumThorns;
	int32 RemovedThorns;
	int32 MaxThorns;
	float Period;
	float ThornLiveTime;
	float ThornInterval;

	float ThornLocation;

	TQueue<class UStaticMeshComponent*> Thorns;
	TSet<class AOgnamCharacter*> Affected;

	FTimerHandle PeriodTimer;
	FTimerHandle RemoveTimer;
};
