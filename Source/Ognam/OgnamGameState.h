// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "OgnamGameState.generated.h"

/**
 *	This state should never be used.
 *	Not even meant for inheritance
 */
UCLASS()
class OGNAM_API AOgnamGameState : public AGameState
{
	GENERATED_BODY()

public:
	AOgnamGameState();

	/*
	**	Binded Functions
	*/
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	int32 GetTeamACount() const;

	UFUNCTION(BlueprintCallable)
	int32 GetTeamBCount() const;

protected:
	/*
	**	Props
	*/
	UPROPERTY(Replicated)
	int32	TeamACount;

	UPROPERTY(Replicated)
	int32	TeamBCount;

};
