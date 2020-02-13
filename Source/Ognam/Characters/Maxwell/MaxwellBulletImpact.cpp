// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellBulletImpact.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AMaxwellBulletImpact::AMaxwellBulletImpact()
{
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> CHBulletImpactParticle(TEXT("NiagaraSystem'/Game/Effect/BulletImpact_System.BulletImpact_System'"));

	BulletImpactSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Bullet Impact"));
	BulletImpactSystem->SetAsset(CHBulletImpactParticle.Object);
	SetRootComponent(BulletImpactSystem);
	BulletImpactSystem->OnSystemFinished.AddDynamic(this, &AMaxwellBulletImpact::OnNiagaraCompleted);
}



void AMaxwellBulletImpact::OnNiagaraCompleted(class UNiagaraComponent* PSystem)
{
	Destroy();
}

void AMaxwellBulletImpact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

