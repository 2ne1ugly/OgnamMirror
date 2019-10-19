// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "BloodhoundSteamLeapAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundSteamLeapAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UBloodhoundSteamLeapAction();

protected:
	virtual void TickChannel(float DeltaTime) override;
	virtual void BeginPostDelay() override;
};
