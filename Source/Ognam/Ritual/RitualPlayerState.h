// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamPlayerstate.h"
#include "RitualPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ARitualPlayerState : public AOgnamPlayerState
{
	GENERATED_BODY()

public:
	ARitualPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void NotifyDeath(AActor* Causer, AActor* Reciever, AController* Instigator, AController* RecieverController) override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	void SetTeamIndex(int32 index);

	UFUNCTION(BlueprintCallable)
	int32 GetTeamIndex() const;

	UFUNCTION(BlueprintCallable)
	FName GetSide() const;

protected:
	/*
	**	Props
	*/
	UPROPERTY(Transient, Replicated)
	int32 TeamIndex;

};
