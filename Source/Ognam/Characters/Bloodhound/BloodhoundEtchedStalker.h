// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "BloodhoundEtchedStalker.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundEtchedStalker : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UBloodhoundEtchedStalker();

protected:
	virtual void ActivateAbility() override;
};
