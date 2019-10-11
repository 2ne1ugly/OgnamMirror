// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "HazelFlameBlastAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelFlameBlastAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UHazelFlameBlastAction();

protected:
	virtual void BeginChannel() override;
};
