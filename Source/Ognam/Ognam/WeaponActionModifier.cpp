// Copyright 2019 Ognam Studios. All Rights Reserved.
#include "WeaponActionModifier.h"
#include "UnrealNetwork.h"
#include "Ognam/OgnamMacro.h"
#include "Weapon.h"
#include "OgnamCharacter.h"

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
	Target->GetWeapon()->ExecuteWeaponActionNotify();
	ExecutePreDelay();
}

void UWeaponActionModifier::NetExecuteAciton_Implementation()
{
	ExecuteAction();
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

	Target->GetWeapon()->FinishWeaponActionNotify();
	if (bRepeat && Target->GetWeapon()->CanBasic())
	{
		ExecuteAction();
	}
}
