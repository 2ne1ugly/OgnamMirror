// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "HazelBurstAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelBurstAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UHazelBurstAction();

protected:
	virtual void BeginChannel() override;

	void ReleaseFireBall();

	/*
	**	Props
	*/
	int32 Count;
	int32 TotalCount;

	FTimerHandle ReleaseTimer;
};
