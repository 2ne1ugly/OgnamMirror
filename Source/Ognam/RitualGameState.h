// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "RitualGameState.generated.h"

/**
 *	for now, I'm calling the teams Green and Blue
 */
UCLASS()
class OGNAM_API ARitualGameState : public AGameState
{
	GENERATED_BODY()

public:
	ARitualGameState();

	/*
	**	Binded Functions
	*/
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void HandleMatchHasStarted() override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	FName GetCurrentOffenseTeam() const;

	UFUNCTION(BlueprintCallable)
	FName GetCurrentDefenseTeam() const;

protected:

	/*
	**	Props
	*/
	TArray<class ARitualPlayerState*>	GreenPlayers;
	TArray<class ARitualPlayerState*>	BluePlayers;

	//Required number score to win
	UPROPERTY(Replicated)
	int32 RequiredScore;

	//Counts from 1
	UPROPERTY(Replicated)
	int32 CurrentRound;

	UPROPERTY(Replicated)
	int32 GreenScore;

	UPROPERTY(Replicated)
	int32 BlueScore;

	UPROPERTY(Replicated)
	FName CurrentOffenseTeam;

	UPROPERTY(Replicated)
	FName CurrentDefenseTeam;
};
