// Fill out your copyright notice in the Description page of Project Settings.


#include "MaxwellVault.h"
#include "Ognam/OgnamCharacter.h"
#include "MaxwellVaultModifier.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "ConstructorHelpers.h"

UMaxwellVault::UMaxwellVault()
{
	AbilityType = EAbilityType::Unique;
	Cooldown = 10.f;

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconTexture(TEXT("Texture2D'/Game/UI/CharacterIcon/Maxwell/Vault.Vault'"));
	Icon = IconTexture.Object;
}

void UMaxwellVault::ActivateAbility()
{
	Target->LaunchCharacter(FVector::UpVector * 1800.f, false, true);
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UMaxwellVault::ApplyModifier);
}

void UMaxwellVault::ApplyModifier()
{
	NewObject<UMaxwellVaultModifier>(Target)->RegisterComponent();
}
