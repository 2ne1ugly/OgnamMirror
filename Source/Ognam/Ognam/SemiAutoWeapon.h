// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Weapon.h"
#include "Ognam/OgnamEnum.h"
#include "SemiAutoWeapon.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API USemiAutoWeapon : public UWeapon
{
	GENERATED_BODY()

public:
	USemiAutoWeapon();

protected:
	virtual void BasicPressed() override;

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerBasicPressed();
	bool ServerBasicPressed_Validate() { return true; }
	virtual void ServerBasicPressed_Implementation();

	virtual bool CanBasic() override;
};
