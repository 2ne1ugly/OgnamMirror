// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OgnamPlayerstate.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AOgnamPlayerstate : public APlayerState
{
	GENERATED_BODY()

public:
	AOgnamPlayerstate();

	UPROPERTY(Replicated)
	int ID;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable)
	int GetID() const;
};
