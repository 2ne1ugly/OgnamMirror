// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "JeraSuppressiveImpactAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UJeraSuppressiveImpactAction : public UActionModifier
{
	GENERATED_BODY()

public:
	UJeraSuppressiveImpactAction();

protected:
	virtual void EndChannel() override;

private:
	class USoundCue* BuildupSound;
};
