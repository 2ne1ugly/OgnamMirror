// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Maxwell.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AMaxwell : public AOgnamCharacter
{
	GENERATED_BODY()

public:
	AMaxwell();

	/*
	**	Binded Function
	*/
	virtual void BeginPlay() override;
};
