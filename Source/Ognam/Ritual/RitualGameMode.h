// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamGameMode.h"
#include "RitualGameMode.generated.h"

/**
 *	Ritual mode is defense/offense mode where 
 *		offense has to kill all Acolytes
 *		defense has to protect the Acolytes, summon the boss, destroy enemy base with it.
 *
 *	There's two ways to end match. I'm trying to do it by calling the endmatch function from state.
 *	In the Actual game, they should be chosen team as they enter the session
 */
UCLASS()
class OGNAM_API ARitualGameMode : public AOgnamGameMode
{
	GENERATED_BODY()

public:
	ARitualGameMode();

	/*
	**	Binded Functions
	*/
	virtual void Tick(float DeltaTime) override;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual bool ReadyToStartMatch_Implementation() override;
	virtual void PostLogin(class APlayerController* NewPlayer) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	// TODO: Make this into a single Respawn to correct pawn instead of overriding this shit
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	//We Handle this here bc we want to make sure that this is called only from server.
	virtual void HandleMatchHasStarted() override;

	/*
	**	Server Functions
	*/
	void KillPlayer(class ARitualPlayerController* PlayerController);
	//void RespawnPlayer(class ARitualPlayerController* PlayerController);
	//void RespawnAllPlayer();
	//void StartFirstRound();
	//void RestartRound();
	//void EndRound();
	//void StartNewRound();

	/*
	** Here we begin the "draft" phase of the round. 
	** We will lock character movement and make them choose their character here
	*/
	void PreRoundBegin();

	/*
	** This is the cleanup after the timer ends from PreRoundBegin()
	** Here we reactivate input and any other cleaning up that needs to be done
	*/
	void PreRoundEnd();

	/*
	** Here we officially start the round, called immediately after PreRoundEnd
	*/
	void BeginRound();

	/*
	** Here we enable special round end effects such as slow motion, and begin the timer to start a new round
	*/
	void PostRoundBegin();

	/*
	** We return the game to it's normal state here (turn off slow motion
	*/
	void PostRoundEnd();

	/*
	** We do calulations to determine the match winner, award points, clean up the map, and respawn players
	*/
	void EndRound();

	/*
	**	Exported Props
	*/
	TArray<class ARitualPlayerController*> PlayerControllers;

	/* Timer for character selection */
	FTimerHandle PostRoundTimer;

	/* Timer for slow motion / after round delay */
	FTimerHandle PreRoundTimer;

	bool bRoundEnded;
	float PostRoundTime;
	float CharacterSelectionTime;
};
