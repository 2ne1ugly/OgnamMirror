// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "OgnamCharacter.h"

// Sets default values for this component's properties
UWeapon::UWeapon()
{

}

void UWeapon::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<AOgnamCharacter>(GetOwner());

	BasicPressHandle = Target->OnBasicPressed.AddUObject(this, &UWeapon::BasicPressed);
	BasicReleaseHandle = Target->OnBasicReleased.AddUObject(this, &UWeapon::BasicReleased);
}

void UWeapon::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Target->OnBasicPressed.Remove(BasicPressHandle);
	Target->OnBasicReleased.Remove(BasicReleaseHandle);
}

void UWeapon::BasicPressed()
{
}

void UWeapon::BasicReleased()
{
}
