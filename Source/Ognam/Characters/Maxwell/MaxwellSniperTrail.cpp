// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "MaxwellSniperTrail.h"
#include "Particles/ParticleSystemComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AMaxwellSniperTrail::AMaxwellSniperTrail()
{
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UParticleSystem> ShotParticle(TEXT("ParticleSystem'/Game/ParagonMurdock/FX/Particles/Abilities/Primary/FX/P_Murdock_Bullet_Trail_Smoke_Spline.P_Murdock_Bullet_Trail_Smoke_Spline'"));
	
	BulletTrailSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Bullet Trail"));
	BulletTrailSystem->SetTemplate(ShotParticle.Object);
	BulletTrailSystem->SetupAttachment(RootComponent);
	BulletTrailSystem->SetRelativeLocation(FVector::ZeroVector);
	BulletTrailSystem->bAutoDestroy = true;
	RootComponent = BulletTrailSystem;
	bAutoDestroyWhenFinished = true;
}

