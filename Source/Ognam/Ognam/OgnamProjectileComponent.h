// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "OgnamProjectileComponent.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UOgnamProjectileComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()

public:
	virtual FVector ComputeAcceleration(const FVector& InVelocity, float DeltaTime) const override;

	float DirecitionalAcceleration;
};
