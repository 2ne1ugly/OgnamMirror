// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "HereiraMolotovBurning.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Ognam/OgnamCharacter.h"

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
	return Target->HasAuthority() && Super::ShouldEnd();
}

void UHereiraMolotovBurning::BeginModifier()
{
	Super::BeginModifier();
	GetWorld()->GetTimerManager().SetTimer(TickTimer, this, &UHereiraMolotovBurning::TickDamage, .5f, true);
}

void UHereiraMolotovBurning::TickDamage()
{
	if (Target->HasAuthority())
	{
		UGameplayStatics::ApplyDamage(Target, 10.f, Instigator->GetController(), nullptr, nullptr);
	}
}
