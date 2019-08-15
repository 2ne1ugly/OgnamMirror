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

protected:
	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere)
	FName Team;
};
