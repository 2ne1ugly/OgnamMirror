// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OgnamGameMode.h"
#include "RitualGameMode.generated.h"

/**
 *	Ritual mode is defense/offense mode where 
 *		offense has to kill all Acolytes
 *		defense has to protect the Acolytes, summon the boss, destroy enemy base with it.
 *
 *	There's two ways to end match. I'm trying to do it by calling the endmatch function from state.
 *	In the Actual game, they should be chosen team as the
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
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual bool ReadyToStartMatch_Implementation() override;
	virtual void PostLogin(class APlayerController* NewPlayer) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
};
