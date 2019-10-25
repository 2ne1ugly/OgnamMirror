// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/Weapon.h"
#include "AutoWeapon.generated.h"

/**
 *	Auto as if hold to shoot, release to not shoot
 */
UCLASS()
class OGNAM_API UAutoWeapon : public UWeapon
{
	GENERATED_BODY()

public:
	UAutoWeapon();

protected:
	virtual void BasicPressed() override;
	virtual void BasicReleased() override;

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerBasicPressed();
	bool ServerBasicPressed_Validate() { return true; }
	virtual void ServerBasicPressed_Implementation();

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerBasicReleased();
	bool ServerBasicReleased_Validate() { return true; }
	virtual void ServerBasicReleased_Implementation();
};
