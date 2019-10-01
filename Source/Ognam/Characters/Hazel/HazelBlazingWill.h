// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Ability.h"
#include "HazelBlazingWill.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelBlazingWill : public UAbility
{
	GENERATED_BODY()
	
public:
	UHazelBlazingWill();

	virtual void BeginPlay() override;
};
