// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "OgnamGameMode.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AOgnamGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual bool ReadyToStartMatch_Implementation() override;
	virtual void PostLogin(class APlayerController* NewPlayer) override;

	UPROPERTY()
	TArray<class APlayerController*> PlayerControllers;

	UPROPERTY(EditAnywhere)
	int32 MaxNumPlayers = 2;
};
