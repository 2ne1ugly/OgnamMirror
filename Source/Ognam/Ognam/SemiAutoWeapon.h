// Copyright 2019 Ognam Studios. All Rights Reserved.
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

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerBasicPressed();
	bool ServerBasicPressed_Validate() { return true; }
	virtual void ServerBasicPressed_Implementation();

	virtual bool CanBasic() override;
};
