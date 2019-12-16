// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Asha.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AAsha : public AOgnamCharacter
{
	GENERATED_BODY()
	
public:
	AAsha();

	virtual void BeginPlay() override;
};
