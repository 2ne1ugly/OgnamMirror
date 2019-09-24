// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Gelasius.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AGelasius : public AOgnamCharacter
{
	GENERATED_BODY()
	
public:
	AGelasius();

	virtual void BeginPlay() override;
};
