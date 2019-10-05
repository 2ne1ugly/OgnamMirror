// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "BloodhoundMarked.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundMarked : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UBloodhoundMarked();

	void SetInstigator(APawn* Pawn);
	APawn* GetInstigator() const;
	void Consume();

	virtual bool ShouldEnd() override;

protected:
	APawn* Instigator;
	bool bConsumed;
};
