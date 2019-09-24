// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "IsmaelLuxAeterna.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UIsmaelLuxAeterna : public UPromptActiveAbility
{
	GENERATED_BODY()
	
public:
	UIsmaelLuxAeterna();

protected:
	virtual void ActivateAbility() override;
};
