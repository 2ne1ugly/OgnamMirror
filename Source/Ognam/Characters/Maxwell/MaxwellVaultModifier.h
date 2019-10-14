// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "MaxwellVaultModifier.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellVaultModifier : public UModifier
{
	GENERATED_BODY()

public:
	UMaxwellVaultModifier();

	virtual bool ShouldEnd() override;

	virtual void TickModifier(float DeltaTime) override;
};
