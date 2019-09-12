// Fill out your copyright notice in the Description page of Project Settings.


#include "Modifier.h"
#include "OgnamCharacter.h"

UModifier::UModifier()
{
	SetIsReplicated(true);
}

bool UModifier::ShouldEnd()
{
	return false;
}

void UModifier::TickModifier(float DeltaTime)
{
}

void UModifier::BeginPlay()
{
	Super::BeginPlay();

	Target = Cast<AOgnamCharacter>(GetOwner());
	if (!Target)
	{
		UE_LOG(LogTemp, Error, TEXT("Modifier applied to non-ognam character"));
		return;
	}
	BeginModifier();
	Target->Modifiers.Add(this);
}

void UModifier::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (!Target)
	{
		UE_LOG(LogTemp, Error, TEXT("Modifier applied to non-ognam character"));
		return;
	}
	EndModifier();
	Target->Modifiers.Remove(this);
}

void UModifier::BeginModifier()
{
}

void UModifier::EndModifier()
{
}
