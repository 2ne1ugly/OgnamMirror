// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OgnamPlayerController.h"
#include "RitualPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ARitualPlayerController : public AOgnamPlayerController
{
	GENERATED_BODY()

public:
	/*
	**	Overritten Function
	*/
	virtual void Die() override;
};
