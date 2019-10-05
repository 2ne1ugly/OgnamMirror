// Fill out your copyright notice in the Description page of Project Settings.

#include "BloodhoundMarked.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
UBloodhoundMarked::UBloodhoundMarked()
{
	Duration = 5.f;
}

void UBloodhoundMarked::SetInstigator(APawn* Pawn)
{
	Instigator = Pawn;
}

APawn* UBloodhoundMarked::GetInstigator() const
{
	return Instigator;
}

void UBloodhoundMarked::Consume()
{
	if (Instigator)
	{
		UGameplayStatics::ApplyDamage(GetOwner(), 50.f, Instigator->GetController(), Instigator, nullptr);
	}
	bConsumed = true;
}

bool UBloodhoundMarked::ShouldEnd()
{
	return Super::ShouldEnd() || bConsumed;
}
