// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "BloodhoundWithholdAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundWithholdAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UBloodhoundWithholdAction();

protected:
	virtual void BeginChannel() override;
	virtual void TickChannel(float DeltaTime) override;
	virtual void EndChannel() override;

	UFUNCTION(NetMulticast, Unreliable)
	void HideTarget();
	void HideTarget_Implementation();

	UFUNCTION(NetMulticast, Unreliable)
	void ShowTarget();
	void ShowTarget_Implementation();

	APawn* Instigator;
};
