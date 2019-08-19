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

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerThrowLeft();
	bool ServerThrowLeft_Validate() { return true; };
	void ServerThrowLeft_Implementation();

	UFUNCTION(NetMulticast, Unreliable)
	void MultiCastThrowLeft();
	void MultiCastThrowLeft_Implementation();


	/*
	**	Components
	*/
	int32 NumBalls;
	int32 MaxNumBalls;
	float ChargeTime;
	float ChargeTimePerBall;
	float BallRotation;
	float BallRotationSpeed;
};
