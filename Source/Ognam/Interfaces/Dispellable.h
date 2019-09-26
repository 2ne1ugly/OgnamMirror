// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ognam/OgnamEnum.h"
#include "Dispellable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDispellable : public UInterface
{
	GENERATED_BODY()
};

/**
 *	Meant to be used in modifiers && weapons && abilities.
 *	Makes it able to "cancel" their ability on specific status effects or action inputs.
 *	Each Behaviors should be defined on each classes.
 */
class OGNAM_API IDispellable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void StatusEffectApplied(EStatusEffect StatusEffect) = 0;
	virtual void ActionTaken(EActionType ActionType) = 0;

};
