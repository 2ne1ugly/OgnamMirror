// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MaxwellSniperTrail.generated.h"

UCLASS()
class OGNAM_API AMaxwellSniperTrail : public AActor
{
	GENERATED_BODY()
	
public:	
	AMaxwellSniperTrail();

protected:
	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* BulletTrailSystem;
};
