// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OgnamPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AOgnamPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AOgnamPlayerState();

	/*
	**	Binded Functions
	*/
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void CopyProperties(class APlayerState* PlayerState) override;
	virtual void OverrideWith(class APlayerState* PlayerState) override;
protected:

	/*
	**	Props
	*/
	UPROPERTY(Replicated)
	FString Name;

	UPROPERTY(Replicated)
	int32 NumKill;

	UPROPERTY(Replicated)
	int32 NumDeath;
};
