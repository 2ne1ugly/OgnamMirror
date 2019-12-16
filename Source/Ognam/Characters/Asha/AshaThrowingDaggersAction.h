// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/WeaponActionModifier.h"
#include "AshaThrowingDaggersAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UAshaThrowingDaggersAction : public UWeaponActionModifier
{
	GENERATED_BODY()
	
public:
	UAshaThrowingDaggersAction();

	virtual void BeginChannel() override;

protected:
	float BaseDamage;
};
