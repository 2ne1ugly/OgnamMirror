// Fill out your copyright notice in the Description page of Project Settings.

#include "JeraCrystalArms.h"
#include "Components/BoxComponent.h"
#include "Ognam/OgnamCharacter.h"
#include "Kismet/GameplayStatics.h"

UJeraCrystalArms::UJeraCrystalArms()
{
	TriggerClass = UBoxComponent::StaticClass();
	PreSwing = .25f;
	PeriSwing = .25f;
	PostSwing = .45f;
}

void UJeraCrystalArms::BeginPlay()
{
	Super::BeginPlay();
	BoxTrigger = Cast<UBoxComponent>(Trigger);
	BoxTrigger->bHiddenInGame = false;
	BoxTrigger->AttachTo(Target->GetRootComponent());
	BoxTrigger->SetRelativeLocation(FVector(100.f, 0.f, 0.f));
	BoxTrigger->SetBoxExtent(FVector(100.f, 100.f, 100.f));
	BoxTrigger->SetVisibility(false);
}

void UJeraCrystalArms::StartPeriSwing()
{
	Super::StartPeriSwing();
	BoxTrigger->SetVisibility(true);
}

void UJeraCrystalArms::StartPostSwing()
{
	Super::StartPostSwing();
	BoxTrigger->SetVisibility(false);
}

void UJeraCrystalArms::CharacterStrike(AOgnamCharacter* OtherCharacter)
{
	UGameplayStatics::ApplyDamage(OtherCharacter, 40.f, Target->GetController(), Target, nullptr);
}
