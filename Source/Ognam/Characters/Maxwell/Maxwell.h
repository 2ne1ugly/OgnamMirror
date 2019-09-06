// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Maxwell.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AMaxwell : public AOgnamCharacter
{
	GENERATED_BODY()

public:
	AMaxwell();

	/*
	**	Binded functions
	*/
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

protected:
	//basic
	void StartCharge();

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerStartCharge();
	bool ServerStartCharge_Validate() { return true; };
	void ServerStartCharge_Implementation();

	void FireBullet();

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerFireBullet();
	bool ServerFireBullet_Validate() { return true; };
	void ServerFireBullet_Implementation();

	//sub
	void ToggleAimDown();

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerToggleAimDown();
	bool ServerToggleAimDown_Validate() { return true; };
	void ServerToggleAimDown_Implementation();

	//Mobility
	void ShadowShift();

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerShadowShift();
	bool ServerShadowShift_Validate() { return true; };
	void ServerShadowShift_Implementation();
};
