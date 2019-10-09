// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponActionModifier.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamMacro.h"

UWeaponActionModifier::UWeaponActionModifier()
{
	SetNetAddressable();	//this will make same object get same name.
}

bool UWeaponActionModifier::ShouldEnd()
{
	return false;
}

void UWeaponActionModifier::BeginModifier()
{
	//Does not activate execute rightaway.
}

void UWeaponActionModifier::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponActionModifier, bRepeat);
}

void UWeaponActionModifier::ExecuteAction()
{
	if (IsRunning())
	{
		O_LOG(TEXT("Execute weapon action when already executed"));
		return;
	}
	bInterrupted = false;
	ExecutePreDelay();
}

void UWeaponActionModifier::NetExecuteAciton_Implementation()
{
	if (IsRunning())
	{
		O_LOG(TEXT("Execute weapon action when already executed"));
		return;
	}
	bInterrupted = false;
	ExecutePreDelay();
}

void UWeaponActionModifier::SetRepeat(bool Value)
{
	bRepeat = Value;
}

bool UWeaponActionModifier::IsRunning() const
{
	return Stage != EActionStage::PreAction;
}

void UWeaponActionModifier::FinishPostDelay()
{
	EndPostDelay();
	Stage = EActionStage::PreAction;
	if (bRepeat)
	{
		ExecuteAction();
	}
}
