// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HazelFlamePillar.generated.h"

UCLASS()
class OGNAM_API AHazelFlamePillar : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Collision;

public:
	AHazelFlamePillar();

	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ActivateCollision();

	/*
	**	Props
	*/
	float BaseDamage;
	float ActivationTime;
	FTimerHandle ActivationTimer;

	TSet<class AOgnamCharacter*> AffectedCharacters;
};
