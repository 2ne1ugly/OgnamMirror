// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamGameState.h"
#include "RitualGameState.generated.h"

/**
 *	for now, I'm calling the teams Green and Blue
 */
UCLASS()
class OGNAM_API ARitualGameState : public AOgnamGameState
{
	GENERATED_BODY()

public:
	ARitualGameState();

	/*
	**	Binded Functions
	*/
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

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
	float GetRoundStartTime() const;

	UFUNCTION(BlueprintCallable)
	float GetPhaseStartTime() const;

	UFUNCTION(BlueprintCallable)
	float GetPhaseGivenTime() const;

	UFUNCTION(BlueprintCallable)
	float GetPhaseRemainingTime() const;

	UFUNCTION(BlueprintCallable)
	const FString GetFormatRemainingTime() const;

	UFUNCTION(BlueprintCallable)
	bool IsRoundEnding() const;

	UFUNCTION(BlueprintCallable)
	bool IsPreRound() const;

	UFUNCTION(BlueprintCallable)
	void SetPreRoundStage(bool bIsPreRound);

	UFUNCTION(BlueprintCallable)
	bool IsShrineBeingCaptured() const;

	UFUNCTION(Netmulticast, Unreliable)
	void NetStartSlowMotion();
	void NetStartSlowMotion_Implementation();

	UFUNCTION(Netmulticast, Reliable)
	void NetEndSlowMotion();
	void NetEndSlowMotion_Implementation();

	/*
	**	Exported Functions
	*/
	void StartNewRound();
	void SwitchSides();
	bool ShouldEndMatch();
	bool ShouldEndRound();
	void DecideRoundWinner();
	void UpdateProperties();
	void SetRoundEnding(bool b);

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

	//Required number score to win
	UPROPERTY(Replicated)
	int32 RequiredScore;

	//Counts from 1
	UPROPERTY(Transient, Replicated)
	int32 CurrentRound;

	UPROPERTY(Transient, Replicated)
	int32 GreenScore;

	UPROPERTY(Transient, Replicated)
	int32 BlueScore;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	FName CurrentOffenseTeam;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	FName CurrentDefenseTeam;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	int32 NumGreenPlayers;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	int32 NumBluePlayers;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	int32 GreenAliveCount;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	int32 BlueAliveCount;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	float RoundStartTime;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	float PhaseStartTime;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	float PhaseGivenTime;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	bool bRoundEnding;

	UPROPERTY(EditAnywhere)
	float DilationAmount;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	bool bPreRound;

	UPROPERTY(Transient, VisibleAnywhere, Replicated)
	bool bIsShrineBeingCaptured;
};
