// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "BloodhoundPiercingThornsAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundPiercingThornsAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UBloodhoundPiercingThornsAction();

	virtual void TickPreDelay(float DeltaTime) override;
	virtual void BeginChannel() override;
};
