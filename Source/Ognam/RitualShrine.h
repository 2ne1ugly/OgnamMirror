// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RitualShrine.generated.h"

UCLASS()
class OGNAM_API ARitualShrine : public AActor
{
	GENERATED_BODY()
	
public:	
	ARitualShrine();

	/*
	**	Binded Function
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
