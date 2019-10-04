// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "BloodhoundPiercingThorns.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundPiercingThorns : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UBloodhoundPiercingThorns();

protected:
	virtual void ActivateAbility() override;
};
