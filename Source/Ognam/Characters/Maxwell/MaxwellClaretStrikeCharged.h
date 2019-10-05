// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/Modifier.h"
#include "MaxwellClaretStrikeCharged.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellClaretStrikeCharged : public UModifier
{
	GENERATED_BODY()

public:
	UMaxwellClaretStrikeCharged();

	virtual bool ShouldEnd() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool Use();

protected:

	/*
	**	Props
	*/
	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	bool bUsed;
};
