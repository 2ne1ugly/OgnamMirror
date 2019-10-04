// Fill out your copyright notice in the Description page of Project Settings.


#include "HazelEnhancedFlamePilarBurning.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Ognam/OgnamCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"

UHazelEnhancedFlamePilarBurning::UHazelEnhancedFlamePilarBurning()
{
	Duration = 3.f;
	TickPeriod = .5f;
}

void UHazelEnhancedFlamePilarBurning::BeginModifier()
{
	Super::BeginModifier();
	GetWorld()->GetTimerManager().SetTimer(DamageTickTimer, this, &UHazelEnhancedFlamePilarBurning::DamageTick, TickPeriod, true);
}

void UHazelEnhancedFlamePilarBurning::SetInstigator(APawn* _Instigator)
{
	Instigator = _Instigator;
}

void UHazelEnhancedFlamePilarBurning::DamageTick()
{
	if (Target->HasAuthority())
	{
		UGameplayStatics::ApplyDamage(GetOwner(), 5.f, Instigator->GetController(), nullptr, nullptr);
	}
}
