// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/SemiAutoClipWeapon.h"
#include "HereiraCrossbow.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraCrossbow : public USemiAutoClipWeapon
{
	GENERATED_BODY()

public:
	UHereiraCrossbow();

protected:
	//Server call
	virtual void FireBullet();

	friend class AHereira;
	friend class AOgnamCharacter;
};
