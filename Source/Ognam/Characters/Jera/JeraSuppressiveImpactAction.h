// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "JeraSuppressiveImpactAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UJeraSuppressiveImpactAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UJeraSuppressiveImpactAction();

protected:
	virtual void EndChannel() override;
};
