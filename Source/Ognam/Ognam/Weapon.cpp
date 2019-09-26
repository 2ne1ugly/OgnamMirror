// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "OgnamCharacter.h"

// Sets default values for this component's properties
UWeapon::UWeapon()
{
	SetNetAddressable();
	SetIsReplicated(true);
}

bool UWeapon::IsSupportedForNetworking() const
{
	return true;
}

void UWeapon::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<AOgnamCharacter>(GetOwner());

	BasicPressHandle = Target->OnBasicPressed.AddUObject(this, &UWeapon::BasicPressed);
	BasicReleaseHandle = Target->OnBasicReleased.AddUObject(this, &UWeapon::BasicReleased);
	if (bBindSub)
	{
		SubPressHandle = Target->OnSubPressed.AddUObject(this, &UWeapon::SubPressed);
		SubReleaseHandle = Target->OnSubReleased.AddUObject(this, &UWeapon::SubReleased);
	}
}

void UWeapon::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Target->OnBasicPressed.Remove(BasicPressHandle);
	Target->OnBasicReleased.Remove(BasicReleaseHandle);
	if (SubPressHandle.IsValid())
	{
		Target->OnSubPressed.Remove(SubPressHandle);
		Target->OnSubReleased.Remove(SubReleaseHandle);
	}
}

void UWeapon::BasicPressed()
{
}

void UWeapon::BasicReleased()
{
}

void UWeapon::SubPressed()
{
}

void UWeapon::SubReleased()
{
}
