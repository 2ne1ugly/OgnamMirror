// Copyright 2019 Ognam Studios. All Rights Reserved.
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
	virtual void BeginPostDelay() override;
	virtual void TickPostDelay(float DeltaTime) override;
	virtual void EndPostDelay() override;

	APawn* Instigator;
	TArray<FVector> SavedLocations;
	TArray<FRotator> SavedRotations;
	TArray<class UStaticMeshComponent*> Metals;
};
