// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "HazelBursting.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UHazelBursting : public UModifier
{
	GENERATED_BODY()

public:
	UHazelBursting();

	virtual bool ShouldEnd() override;
	virtual void BeginModifier() override;

protected:
	void ReleaseFireBall();

	/*
	**	Props
	*/
	int32 Count;
	int32 TotalCount;
	float Duration;

	FTimerHandle ReleaseTimer;
};
