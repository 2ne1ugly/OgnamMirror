// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "OgnamGameState.generated.h"

/**
 *	This state should never be used.
 *	Not even meant for inheritance
 */
UCLASS()
class OGNAM_API AOgnamGameState : public AGameState
{
	GENERATED_BODY()

public:
	AOgnamGameState();

	/*
	**	Binded Functions
	*/
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;


	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	int32 GetTeamACount() const;

	UFUNCTION(BlueprintCallable)
	int32 GetTeamBCount() const;

	UFUNCTION(BlueprintCallable)
	FString GetServerIP() const;

protected:
	/*
	**	Props
	*/
	UPROPERTY(Transient, Replicated)
	int32	TeamACount;

	UPROPERTY(Transient, Replicated)
	int32	TeamBCount;

	UPROPERTY(Transient, Replicated)
	FString ServerAddress;

};
