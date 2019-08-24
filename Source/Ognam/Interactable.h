// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OGNAM_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetInteractDistance() const = 0;
	virtual float GetInteractDuration() const = 0;
	virtual bool CanInteractWithController(const APlayerController* PlayerController) const = 0;

	UFUNCTION(NetMulticast, Unreliable, WithValidation)
	virtual void BeInteracted(APlayerController* PlayerController);
	virtual bool BeInteracted_Validate(APlayerController* PlayerController) { return true; };
	virtual void BeInteracted_Implementation(APlayerController* PlayerController) = 0;
};
