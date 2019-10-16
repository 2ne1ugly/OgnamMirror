// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "BloodhoundHuntingHour.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundHuntingHour : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UBloodhoundHuntingHour();

	virtual void ActivateAbility() override;
};
