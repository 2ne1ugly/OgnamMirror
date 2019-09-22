// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JeraRadiantDiveDropPoint.generated.h"

UCLASS()
class OGNAM_API AJeraRadiantDiveDropPoint : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* PlaceHolder;
public:	
	// Sets default values for this actor's properties
	AJeraRadiantDiveDropPoint();
	virtual void BeginPlay() override;
};
