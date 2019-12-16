// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "AshaFanofKnivesAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UAshaFanofKnivesAction : public UActionModifier
{
	GENERATED_BODY()
	
public:
	UAshaFanofKnivesAction();

protected:
	virtual void BeginChannel() override;
};
