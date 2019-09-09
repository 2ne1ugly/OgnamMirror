// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Hereira/HereiraArrow.h"
#include "HereiraExplosiveArrow.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AHereiraExplosiveArrow : public AHereiraArrow
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ParticleSystem;

protected:
	/*
	**	Binded Functions
	*/
	virtual void BeginPlay() override;
	virtual void EndLifeSpan();
	virtual void OnCharacterHit(class AOgnamCharacter* OtherCharacter, const FHitResult& SweepResult) override;
	virtual void OnActorHit(class AActor* OtherCharacter, const FHitResult& SweepResult);

public:
	AHereiraExplosiveArrow();
};
