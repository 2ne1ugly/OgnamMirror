// Fill out your copyright notice in the Description page of Project Settings.


#include "JeraPunchImpact.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AJeraPunchImpact::AJeraPunchImpact()
{
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> CHBulletImpactParticle(TEXT("NiagaraSystem'/Game/Effect/JeraPunchImpact_System.JeraPunchImpact_System'"));

	BulletImpactSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Punch Impact"));
	BulletImpactSystem->SetAsset(CHBulletImpactParticle.Object);
	SetRootComponent(BulletImpactSystem);
	BulletImpactSystem->OnSystemFinished.AddDynamic(this, &AJeraPunchImpact::OnNiagaraCompleted);

}

void AJeraPunchImpact::OnNiagaraCompleted(UNiagaraComponent* PSystem)
{
	//Destroy();
}

// Called every frame
void AJeraPunchImpact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

