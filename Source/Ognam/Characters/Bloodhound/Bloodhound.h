// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "Bloodhound.generated.h"

/**
 *	Cthulhu/demon possessed? Steampunk robot machine thing.
 */
UCLASS()
class OGNAM_API ABloodhound : public AOgnamCharacter
{
	GENERATED_BODY()

public:
	ABloodhound();

	virtual void BeginPlay() override;
};
