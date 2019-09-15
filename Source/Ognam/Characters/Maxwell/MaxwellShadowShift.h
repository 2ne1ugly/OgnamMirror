// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActiveAbility.h"
#include "MaxwellShadowShift.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellShadowShift : public UActiveAbility
{
	GENERATED_BODY()

public:
	UMaxwellShadowShift();

protected:
	virtual void OnButtonPressed() override;
};
