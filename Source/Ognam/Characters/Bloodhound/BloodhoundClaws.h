// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/AutoWeapon.h"
#include "BloodhoundClaws.generated.h"

/**
 *	Todo: make leap attack.
 */
UCLASS()
class OGNAM_API UBloodhoundClaws : public UAutoWeapon
{
	GENERATED_BODY()

public:
	UBloodhoundClaws();

protected:
	virtual void ServerBasicPressed_Implementation() override;
};
