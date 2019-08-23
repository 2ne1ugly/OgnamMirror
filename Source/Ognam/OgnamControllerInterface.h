// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OgnamControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UOgnamControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *	Place something Genericly needed for each game
 */
class OGNAM_API IOgnamControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnPawnDeath() = 0;
};
