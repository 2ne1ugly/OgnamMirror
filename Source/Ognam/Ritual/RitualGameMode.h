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
	void RespawnPlayer(class ARitualPlayerController* PlayerController);
	void RespawnAllPlayer();
	void StartFirstRound();
	void RestartRound();
	void EndRound();

	/*
	**	Exported Props
	*/
	TArray<class ARitualPlayerController*> PlayerControllers;
};
