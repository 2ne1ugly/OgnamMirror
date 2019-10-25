// Copyright 2019 Ognam Studios. All Rights Reserved.
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
	virtual void TickChannel(float DeltaTime) override;

	void ReleaseFireBall();

	/*
	**	Props
	*/
	int32 Count;
	int32 TotalCount;

	FTimerHandle ReleaseTimer;
};
