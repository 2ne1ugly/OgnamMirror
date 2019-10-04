// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "BloodhoundEtchedStalkerAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundEtchedStalkerAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UBloodhoundEtchedStalkerAction();

	virtual void EndChannel() override;
};
