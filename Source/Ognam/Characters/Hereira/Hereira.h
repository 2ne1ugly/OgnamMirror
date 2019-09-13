// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "HereiraArrow.h"
#include "HereiraExplosiveArrow.h"
#include "Hereira.generated.h"

/**
 *	A Masked Woman
 */
UCLASS()
class OGNAM_API AHereira : public AOgnamCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UAudioComponent* ShotAudio;

public:
	AHereira();

	/*
	**	Binded Function
	*/
	virtual void BeginPlay() override;
};
