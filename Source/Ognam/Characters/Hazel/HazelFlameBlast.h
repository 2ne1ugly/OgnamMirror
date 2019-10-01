// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "HazelFlameBlast.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelFlameBlast : public UPromptActiveAbility
{
	GENERATED_BODY()
	
public:
	UHazelFlameBlast();

protected:
	virtual void ActivateAbility() override;
};
