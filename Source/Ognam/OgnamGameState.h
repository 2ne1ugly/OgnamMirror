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

	UPROPERTY(Replicated)
	int32	TeamACount = 1;

	UPROPERTY(Replicated)
	int32	TeamBCount = 1;


protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	int32 GetTeamACount() const;

	UFUNCTION(BlueprintCallable)
	int32 GetTeamBCount() const;
};
