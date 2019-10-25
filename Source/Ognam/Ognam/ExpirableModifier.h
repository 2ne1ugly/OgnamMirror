// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "ExpirableModifier.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UExpirableModifier : public UModifier
{
	GENERATED_BODY()

public:
	UExpirableModifier();

	/*
	**	Inherited Funcitons
	*/
	virtual bool ShouldEnd() override;
	virtual void TickModifier(float DeltaTime) override;

protected:
	/*
	**	Make sure to override Begin Modifier with specific duration.
	*/
	virtual void BeginModifier() override;
	virtual void EndModifier() override;

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere)
	float Duration;

	FTimerHandle DurationTimer;
};
