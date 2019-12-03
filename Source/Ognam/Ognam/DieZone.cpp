// Fill out your copyright notice in the Description page of Project Settings.


#include "DieZone.h"
#include "Ognam/OgnamCharacter.h"
#include "Kismet/GameplayStatics.h"
ADieZone::ADieZone()
{
	OnActorBeginOverlap.AddDynamic(this, &ADieZone::BeginActorOverlap);
}

void ADieZone::BeginActorOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (!Cast<AOgnamCharacter>(OtherActor))
	{
		return;
	}\
	UGameplayStatics::ApplyDamage(OtherActor, 10000.f, nullptr, nullptr, nullptr);
}
