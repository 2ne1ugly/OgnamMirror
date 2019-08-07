// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "OgnamGameState.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AOgnamGameState : public AGameState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Replicated)
	int32	TeamACount = 1;

	UPROPERTY(EditAnywhere, Replicated)
	int32	TeamBCount = 1;

	//Remember that list of players are provided in PlayerArray
	//also, to send "Events" to clinets, check RPC
	//client side Events are also done by RPC
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	int32 GetTeamACount() const;

	UFUNCTION(BlueprintCallable)
	int32 GetTeamBCount() const;
};
