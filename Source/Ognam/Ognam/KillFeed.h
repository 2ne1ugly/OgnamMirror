// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "TimerManager.h"
#include "KillFeed.generated.h"

UCLASS()
class OGNAM_API UKillFeed : public UObject
{
	GENERATED_BODY()
	
public:	
	UKillFeed();

	UPROPERTY(BlueprintReadOnly)
	class AOgnamPlayerState* Killer;

	UPROPERTY(BlueprintReadOnly)
	class AOgnamPlayerState* Receiver;
	FTimerHandle LifetimeHandle;

	float LifetimeDuration = 5.f;
};
