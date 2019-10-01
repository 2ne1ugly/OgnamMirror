// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/AutoClipWeapon.h"
#include "HazelPyromancy.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelPyromancy : public UAutoClipWeapon
{
	GENERATED_BODY()

public:
	UHazelPyromancy();

	virtual void FireBullet() override;
};
