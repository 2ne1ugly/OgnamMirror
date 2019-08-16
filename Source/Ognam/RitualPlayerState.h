// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RitualPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ARitualPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ARitualPlayerState();

	/*
	**	Binded Function
	*/
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	void SetTeam(FName name);

	UFUNCTION(BlueprintCallable)
	FName GetTeam() const;

	UFUNCTION(BlueprintCallable)
	void SetTeamIndex(int32 index);

	UFUNCTION(BlueprintCallable)
	int32 GetTeamIndex() const;

	/*
	**	Exported Function
	*/
	//Gets if offense or not
	UFUNCTION(BlueprintCallable)
	FName GetSide() const;

protected:
	/*
	**	Props
	*/
	UPROPERTY(Replicated, VisibleAnywhere)
	FName Team;

	UPROPERTY(Replicated)
	int32 TeamIndex;
};
