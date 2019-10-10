// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/SemiAutoWeapon.h"
#include "MaxwellSniperRifle.generated.h"

/**
 *	Vampire Sniper
 */
UCLASS()
class OGNAM_API UMaxwellSniperRifle : public USemiAutoWeapon
{
	GENERATED_BODY()

public:
	UMaxwellSniperRifle();

protected:
	//Sub
	//Client call
	virtual void SubPressed() override;

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerToggleAimDown();
	bool ServerToggleAimDown_Validate() { return true; };
	void ServerToggleAimDown_Implementation();
};
