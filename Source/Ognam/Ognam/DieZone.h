// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DieZone.generated.h"

UCLASS()
class OGNAM_API ADieZone : public AActor
{
	GENERATED_BODY()
	
public:	
	ADieZone();

	UFUNCTION()
	void BeginActorOverlap(AActor* OverlappedActor, AActor* OtherActor);


};
