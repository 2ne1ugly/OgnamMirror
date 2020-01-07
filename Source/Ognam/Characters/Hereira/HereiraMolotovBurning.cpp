// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraMolotovBurning.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

UHereiraMolotovBurning::UHereiraMolotovBurning()
{
	Duration = 3.f;
}

void UHereiraMolotovBurning::ResetDuration()
{
	Super::BeginModifier();
}

void UHereiraMolotovBurning::SetInstigator(APawn* _Instigator)
{
	Instigator = _Instigator;
}

bool UHereiraMolotovBurning::ShouldEnd()
{
	return GetOwner()->HasAuthority() && Super::ShouldEnd();
}

void UHereiraMolotovBurning::BeginModifier()
{
	Super::BeginModifier();
	GetWorld()->GetTimerManager().SetTimer(TickTimer, this, &UHereiraMolotovBurning::TickDamage, .5f, true);
}

void UHereiraMolotovBurning::TickDamage()
{
	if (GetOwner()->HasAuthority())
	{
		UGameplayStatics::ApplyDamage(GetOwner(), 10.f, Instigator->GetController(), nullptr, nullptr);
	}
}
