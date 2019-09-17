// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "HereiraWillExplode.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHereiraWillExplode : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UHereiraWillExplode();

	virtual void EndModifier() override;
	
	/*
	**	Getters, Setters
	*/
	void SetInstigator(APawn* Pawn);

protected:
	/*
	**	Props
	*/
	APawn* Instigator;
};
