// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "BloodhoundSteamLeap.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundSteamLeap : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UBloodhoundSteamLeap();

protected:
	virtual void ActivateAbility() override;
};
