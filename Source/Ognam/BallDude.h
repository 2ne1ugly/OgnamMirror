// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OgnamCharacter.h"
#include "BallDude.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ABallDude : public AOgnamCharacter
{
	GENERATED_BODY()

protected:
	/*
	**	Components
	*/
	UPROPERTY(VisibleAnywhere)
	TArray<class UStaticMeshComponent*> Balls;

	UPROPERTY(VisibleAnywhere)
	class UArrowComponent* BallSpinner;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* TrajectoryHost;

	UPROPERTY(VisibleAnywhere)
	TArray<class UStaticMeshComponent*> Trajectory;

public:
	ABallDude();

	/*
	**	Binded Functions
	*/
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


protected:
	/*
	**	Internal Functions
	*/
	void ThrowLeft();
	void StopThrowLeft();

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerThrowLeft(float Charge);
	bool ServerThrowLeft_Validate(float Charge) { return true; };
	void ServerThrowLeft_Implementation(float Charge);

	UFUNCTION(NetMulticast, Unreliable)
	void MultiCastThrowLeft(float Charge);
	void MultiCastThrowLeft_Implementation(float Charge);

	void AddBalls();
	void UseBalls();

	FVector CalculateTrajectoryPosition(float Time, float Charge);
	/*
	**	Props
	*/
	int32 NumBalls;
	int32 MaxNumBalls;
	float BallChargeTime;
	float BallChargeTimePerBall;
	float BallRotation;
	float BallRotationSpeed;
	bool bIsCharging;
	float ChargeTime;
};
