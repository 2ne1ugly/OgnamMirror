// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OgnamPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AOgnamPlayerState : public APlayerState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	float Health;
	//fill all the player specific data

protected:
	//replication reciever kinda
	virtual void CopyProperties(class APlayerState* PlayerState) override;
	virtual void OverrideWith(class APlayerState* PlayerState) override;

};
