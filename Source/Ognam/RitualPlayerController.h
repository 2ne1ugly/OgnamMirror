// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OgnamPlayerController.h"
#include "RitualPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ARitualPlayerController : public AOgnamPlayerController
{
	GENERATED_BODY()

public:
	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	bool GetIsReady() const;

	UFUNCTION(BlueprintCallable)
	FName GetTeam() const;

	UFUNCTION(BlueprintCallable)
	void SetTeam(FName name);

	UFUNCTION(BlueprintCallable)
	int32 GetTeamIndex() const;

	UFUNCTION(BlueprintCallable)
	void SetTeamIndex(int32 index);

	/*
	**	Exported Function
	*/
	UFUNCTION(Client, Reliable)
	void GetReady(int32 index, FName Team);
	void GetReady_Implementation(int32 index, FName Team);

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerReady();
	bool ServerReady_Validate() { return true; };
	void ServerReady_Implementation();

	//Gets if offense or not
	UFUNCTION(BlueprintCallable)
	FName GetSide() const;

protected:
	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere)
	FName Team;

	UPROPERTY(VisibleAnywhere)
	int32 TeamIndex;

	/*
	**	Props
	*/
	bool bIsReady;
};
