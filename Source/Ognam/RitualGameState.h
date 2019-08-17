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
	virtual void Tick(float DeltaTime) override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	FName GetCurrentOffenseTeam() const;

	UFUNCTION(BlueprintCallable)
	FName GetCurrentDefenseTeam() const;

	UFUNCTION(BlueprintCallable)
	int32 GetGreenAliveCount() const;

	UFUNCTION(BlueprintCallable)
	int32 GetBlueAliveCount() const;

	UFUNCTION(BlueprintCallable)
	int32 GetGreenScore() const;

	UFUNCTION(BlueprintCallable)
	int32 GetBlueScore() const;

	UFUNCTION(BlueprintCallable)
	int32 GetNumGreenPlayers() const;

	UFUNCTION(BlueprintCallable)
	int32 GetNumBluePlayers() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentRound() const;

	UFUNCTION(BlueprintCallable)
	void IncNumGreenPlayers();

	UFUNCTION(BlueprintCallable)
	void IncNumBluePlayers();

	/*
	**	Exported Functions
	*/
	//Only Used for server internally
	void StartRound();
	//Only Used for server internally
	void KillPlayer(class ARitualPlayerController* PlayerController);


	/*
	**	Exported Props
	*/
	const FName GreenName = TEXT("Green");
	const FName BlueName = TEXT("Blue");
	const FName DefenseName = TEXT("Defense");
	const FName OffenseName = TEXT("Offense");
protected:
	/*
	**	Internal Functions
	*/
	void EndRound();

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

	UPROPERTY(VisibleAnywhere, Replicated)
	FName CurrentOffenseTeam;

	UPROPERTY(VisibleAnywhere, Replicated)
	FName CurrentDefenseTeam;

	UPROPERTY(VisibleAnywhere, Replicated)
	int32 NumGreenPlayers;

	UPROPERTY(VisibleAnywhere, Replicated)
	int32 NumBluePlayers;

	UPROPERTY(VisibleAnywhere, Replicated)
	int32 GreenAliveCount;

	UPROPERTY(VisibleAnywhere, Replicated)
	int32 BlueAliveCount;

};