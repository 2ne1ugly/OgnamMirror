// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamProjectileComponent.h"

FVector UOgnamProjectileComponent::ComputeAcceleration(const FVector& InVelocity, float DeltaTime) const
{
	FVector Acceleration(FVector::ZeroVector);

	Acceleration.Z += GetGravityZ();
	Acceleration += InVelocity.GetSafeNormal() * DirecitionalAcceleration;

	if (bIsHomingProjectile && HomingTargetComponent.IsValid())
	{
		Acceleration += ComputeHomingAcceleration(InVelocity, DeltaTime);
	}

	return Acceleration;
}
