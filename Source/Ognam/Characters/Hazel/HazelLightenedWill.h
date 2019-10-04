// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Ability.h"
#include "HazelLightenedWill.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelLightenedWill : public UAbility
{
	GENERATED_BODY()
	
public:
	UHazelLightenedWill();

	virtual void BeginPlay() override;
};
