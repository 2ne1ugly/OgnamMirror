// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "HazelDisruptiveBurst.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelDisruptiveBurst : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UHazelDisruptiveBurst();

protected:
	virtual void ActivateAbility() override;
};
 