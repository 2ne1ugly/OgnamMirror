// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Hazel/HazelFlamePillar.h"
#include "HazelEnhancedFlamePillar.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AHazelEnhancedFlamePillar : public AHazelFlamePillar
{
	GENERATED_BODY()

public:
	virtual void DealDamage(class AOgnamCharacter* Character) override;
};
