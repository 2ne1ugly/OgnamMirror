// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "BloodhoundImpactShotgun.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundImpactShotgun : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UBloodhoundImpactShotgun();

protected:
	virtual void ActivateAbility() override;
};
