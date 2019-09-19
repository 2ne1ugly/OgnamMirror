// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "ImpactDamage.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UImpactDamage : public UDamageType
{
	GENERATED_BODY()

public:
	uint32 bCausedByWorld = 0;
	uint32 bScaleMomentumByMass = 1;
	uint32 bRadialDamageVelChange = 0;
	float DamageImpulse = 0.f;
	float DestructibleImpulse = 0.f;
	float DestructibleDamageSpreadScale = 1.f;
	float DamageFalloff = 1.f;
};
