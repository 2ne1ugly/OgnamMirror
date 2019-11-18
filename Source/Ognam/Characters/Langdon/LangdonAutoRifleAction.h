// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/WeaponActionModifier.h"
#include "LangdonAutoRifleAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ULangdonAutoRifleAction : public UWeaponActionModifier
{
	GENERATED_BODY()

public:
	ULangdonAutoRifleAction();

	virtual void BeginChannel() override;

protected:
	UFUNCTION(NetMulticast, Unreliable)
	void NetDrawTrajectory(FVector From, FVector To);
	void NetDrawTrajectory_Implementation(FVector From, FVector To);

	/*
	**	Props
	*/
	float BaseDamage;
};
