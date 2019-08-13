// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "OgnamGameMode.generated.h"

/**
 *	Place things that are generic between game modes.
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
	virtual bool ReadyToStartMatch_Implementation() override;
	virtual void PostLogin(class APlayerController* NewPlayer) override;
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
};
