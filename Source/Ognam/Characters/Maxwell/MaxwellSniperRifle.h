// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/SemiAutoClipWeapon.h"
#include "MaxwellSniperRifle.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellSniperRifle : public USemiAutoClipWeapon
{
	GENERATED_BODY()

public:
	UMaxwellSniperRifle();

protected:
	//Server call
	virtual void FireBullet();

	friend class AOgnamCharacter;
};
