// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Langdon.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ALangdon : public AOgnamCharacter
{
	GENERATED_BODY()

public:
	ALangdon();

	virtual void BeginPlay() override;
};
