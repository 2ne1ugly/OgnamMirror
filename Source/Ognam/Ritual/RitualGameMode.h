// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamGameMode.h"
#include "RitualGameMode.generated.h"

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

	virtual void Logout(class AController* Controller) override;

	/*
	**	Server Functions
	*/
	void KillPlayer(class ARitualPlayerController* PlayerController);

	/*
	** Here we begin the "draft" phase of the round. 
	** We will lock character movement and make them choose their character here
	*/
	void StartPreRound();

	/*
	** This is the cleanup after the timer ends from PreRoundBegin()
	** Here we reactivate input and any other cleaning up that needs to be done
	*/
	void EndPreRound();

	/*
	** Here we officially start the round, called immediately after PreRoundEnd
	*/
	void BeginRound();

	/*
	** Here we enable special round end effects such as slow motion, and begin the timer to start a new round
	*/
	void StartPostRound();

	/*
	** We return the game to it's normal state here (turn off slow motion
	*/
	void EndPostRound();

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
