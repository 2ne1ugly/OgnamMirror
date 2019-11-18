// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "LangdonSteamBracersModifier.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ULangdonSteamBracersModifier : public UActionModifier
{
	GENERATED_BODY()

public:
	ULangdonSteamBracersModifier();

protected:
	virtual void TickChannel(float DeltaTime) override;
};
