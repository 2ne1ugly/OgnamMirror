// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActiveAbility.h"
#include "MaxwellClaretStrike.generated.h"

/**
 *	Potentially make it use  action modifier
 */
UCLASS()
class OGNAM_API UMaxwellClaretStrike : public UActiveAbility
{
	GENERATED_BODY()
	
public:
	UMaxwellClaretStrike();

protected:
	//Client call
	virtual void OnButtonPressed() override;

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerChargeClaretStrike();
	bool ServerChargeClaretStrike_Validate() { return true; }
	void ServerChargeClaretStrike_Implementation();
};
