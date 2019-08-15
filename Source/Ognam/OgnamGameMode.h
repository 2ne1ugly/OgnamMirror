// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "OgnamGameMode.generated.h"

/**
 *	Place things that are generic between game modes.
 *	The reason is because reducing code repeation.
 *	Also, Don't implement functions for "Getting ready" that should be handled in child classes.
 */
UCLASS()
class OGNAM_API AOgnamGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AOgnamGameMode();
	
	/*
	**	Binded Functions
	*/
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

protected:

	/*
	**	Props
	*/
	int32 MaxNumPlayers;
};
