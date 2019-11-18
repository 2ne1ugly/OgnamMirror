// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/PromptActiveAbility.h"
#include "LangdonSteamBracers.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ULangdonSteamBracers : public UPromptActiveAbility
{
	GENERATED_BODY()
	
public:
	ULangdonSteamBracers();

protected:
	//Server Call
	virtual void ActivateAbility() override;
};
