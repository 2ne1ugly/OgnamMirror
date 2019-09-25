// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "JeraDescending.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UJeraDescending : public UModifier
{
	GENERATED_BODY()

public:
	UJeraDescending();

	virtual bool ShouldEnd() override;

	virtual void TickModifier(float DeltaTime) override;
	virtual void EndModifier() override;
};
