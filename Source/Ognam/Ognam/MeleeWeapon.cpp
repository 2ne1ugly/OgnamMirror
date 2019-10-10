// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Ognam/OgnamCharacter.h"
#include "WeaponActionModifier.h"
#include "Ognam/OgnamMacro.h"

UMeleeWeapon::UMeleeWeapon()
{
	//TCHAR Buff[100];
	//memcpy(Buff, TEXT("Hello World"), 100);
	////memcpy(Buff, FString(TEXT("%s(%d): ")).Append(TEXT("HMM")).GetCharArray()., )
}

void UMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (!SwingClass)
	{
		O_LOG_E(TEXT("No Swing Class"));
		return;
	}
	Swing = NewObject<UWeaponActionModifier>(GetOwner(), SwingClass, TEXT("Melee Swing"));
	Swing->RegisterComponent();
}

void UMeleeWeapon::BasicPressed()
{
	if (Target->HasStatusEffect(EStatusEffect::Unarmed))
	{
		return;
	}
	ServerBasicPressed();
}

void UMeleeWeapon::ServerBasicPressed_Implementation()
{
	if (Target->HasStatusEffect(EStatusEffect::Unarmed))
	{
		return;
	}
	Swing->SetRepeat(true);
	if (Swing->GetStage() == EActionStage::PreAction)
	{
		Swing->NetExecuteAciton();
	}
}

void UMeleeWeapon::BasicReleased()
{
	ServerBasicReleased();
}

void UMeleeWeapon::ServerBasicReleased_Implementation()
{
	Swing->SetRepeat(false);
}
