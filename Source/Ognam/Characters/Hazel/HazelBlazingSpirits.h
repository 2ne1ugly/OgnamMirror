// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "HazelBlazingSpirits.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelBlazingSpirits : public UPromptActiveAbility
{
	GENERATED_BODY()

public:
	UHazelBlazingSpirits();

protected:
	virtual void ActivateAbility() override;
};
