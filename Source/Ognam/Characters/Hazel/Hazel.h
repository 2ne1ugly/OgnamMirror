// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Hazel.generated.h"

/**
 *	Flame Wizard
 */
UCLASS()
class OGNAM_API AHazel : public AOgnamCharacter
{
	GENERATED_BODY()

public:
	AHazel();

	virtual void BeginPlay() override;
};
