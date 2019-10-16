// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillFeed.generated.h"

UCLASS()
class OGNAM_API AKillFeed : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKillFeed();

	UPROPERTY(BlueprintReadOnly)
	class AOgnamPlayerState* Killer;

	UPROPERTY(BlueprintReadOnly)
	class AOgnamPlayerState* Receiver;
	FTimerHandle LifetimeHandle;

	float LifetimeDuration = 5.f;

protected:
	// Called when the game starts or when spawned
};
