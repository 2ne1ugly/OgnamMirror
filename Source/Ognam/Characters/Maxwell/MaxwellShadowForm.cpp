// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellShadowForm.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamCharacter.h"

UMaxwellShadowForm::UMaxwellShadowForm()
{
	StatusEffect |= EStatusEffect::Unarmed | EStatusEffect::Silenced | EStatusEffect::Rooted;
	Duration = .2f;
	Direction = FVector::ForwardVector;
}

void UMaxwellShadowForm::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UMaxwellShadowForm, Direction, COND_InitialOnly);
}

void UMaxwellShadowForm::TickModifier(float DeltaTime)
{
	Target->AddActorWorldOffset(Direction * DeltaTime * 1500.f, true);
}

void UMaxwellShadowForm::SetDirection(FVector Vector)
{
	Direction = Vector;
}

