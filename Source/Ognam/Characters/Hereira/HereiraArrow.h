// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HereiraArrow.generated.h"

UCLASS()
class OGNAM_API AHereiraArrow : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* Arrow;
public:	
	AHereiraArrow();

	/*
	**	Binded Functions
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/*
	**	Getters, Setters
	*/
	void SetInitialPosition(FVector Value);
	void SetInitialVelocity(FVector Value);
	void SetGravity(float Value);

protected:
	/*
	**	Internal Functions
	*/
	virtual void EndLifeSpan();
	virtual void OnCharacterHit(class AOgnamCharacter* OtherCharacter, const FHitResult& SweepResult);
	float CalculateFlownDistance();

	//For non Characters
	virtual void OnActorHit(class AActor* OtherCharacter, const FHitResult& SweepResult);

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere, Replicated)
	FTimerHandle LifeSpan;

	UPROPERTY(EditAnywhere, Replicated)
	FVector InitialPosition;

	UPROPERTY(EditAnywhere, Replicated)
	FVector InitialVelocity;

	UPROPERTY(EditAnywhere, Replicated)
	float Gravity;

	bool bIsTraveling;
};
