// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShake.h"
#include "MaxwellSniperRifleRecoil.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UMaxwellSniperRifleRecoil : public UCameraShake
{
	GENERATED_BODY()

public:
	UMaxwellSniperRifleRecoil();

	virtual void PlayShake(class APlayerCameraManager* Camera, float Scale, ECameraAnimPlaySpace::Type InPlaySpace, FRotator UserPlaySpaceRot = FRotator::ZeroRotator) override;
};
