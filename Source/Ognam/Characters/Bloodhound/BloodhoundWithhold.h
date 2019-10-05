// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "BloodhoundWithhold.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundWithhold : public UPromptActiveAbility
{
	GENERATED_BODY()
	
public:
	UBloodhoundWithhold();

protected:
	virtual void ActivateAbility() override;
};
