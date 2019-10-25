// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamPlayerstate.h"
#include "RitualPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRoundStageEvent);

/**
 * 
 */
UCLASS()
class OGNAM_API ARitualPlayerState : public AOgnamPlayerState
{
	GENERATED_BODY()

public:
	ARitualPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void NotifyDeath(AActor* Causer, AActor* Reciever, AController* Instigator, AController* RecieverController) override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	void SetTeamIndex(int32 index);

	UFUNCTION(BlueprintCallable)
	int32 GetTeamIndex() const;

	UFUNCTION(BlueprintCallable)
	FName GetSide() const;

protected:
	/*
	**	Props
	*/
	UPROPERTY(Transient, Replicated)
	int32 TeamIndex;


public:
	/*
	** Here we begin the "draft" phase of the round.
	** We will lock character movement and make them choose their character here
	*/
	UFUNCTION(Client, Reliable)
	void ClientStartPreRound();

	UPROPERTY(BlueprintAssignable)
	FRoundStageEvent OnStartPreRound;

	/*
	** This is the cleanup after the timer ends from PreRoundBegin()
	** Here we reactivate input and any other cleaning up that needs to be done
	*/
	UFUNCTION(Client, Reliable)
	void ClientEndPreRound();

	UPROPERTY(BlueprintAssignable)
	FRoundStageEvent OnEndPreRound;

	/*
	** Here we officially start the round, called immediately after PreRoundEnd
	*/
	UFUNCTION(Client, Reliable)
	void ClientBeginRound();

	UPROPERTY(BlueprintAssignable)
	FRoundStageEvent OnBeginRound;

	/*
	** Here we enable special round end effects such as slow motion, and begin the timer to start a new round
	*/
	UFUNCTION(Client, Reliable)
	void ClientStartPostRound();

	UPROPERTY(BlueprintAssignable)
	FRoundStageEvent OnStartPostRound;

	/*
	** We return the game to it's normal state here (turn off slow motion
	*/
	UFUNCTION(Client, Reliable)
	void ClientEndPostRound();

	UPROPERTY(BlueprintAssignable)
	FRoundStageEvent OnEndPostRound;

	/*
	** We do calulations to determine the match winner, award points, clean up the map, and respawn players
	*/
	UFUNCTION(Client, Reliable)
	void ClientEndRound();

	UPROPERTY(BlueprintAssignable)
	FRoundStageEvent OnEndRound;

};
