// Fill out your copyright notice in the Description page of Project Settings.


#include "AshaDaggersImpact.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "ConstructorHelpers.h"


// Sets default values
AAshaDaggersImpact::AAshaDaggersImpact()
{
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> CHBulletImpactParticle(TEXT("NiagaraSystem'/Game/Effect/HereraBulletImpact_System.HereraBulletImpact_System'"));

	BulletImpactSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Bullet Impact"));
	BulletImpactSystem->SetAsset(CHBulletImpactParticle.Object);
	SetRootComponent(BulletImpactSystem);
	BulletImpactSystem->OnSystemFinished.AddDynamic(this, &AAshaDaggersImpact::OnNiagaraCompleted);

}

void AAshaDaggersImpact::OnNiagaraCompleted(UNiagaraComponent* PSystem)
{
	Destroy();
}

// Called every frame
void AAshaDaggersImpact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

