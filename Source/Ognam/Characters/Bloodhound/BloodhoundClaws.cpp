// Fill out your copyright notice in the Description page of Project Settings.


#include "BloodhoundClaws.h"
#include "BloodhoundClawsAction.h"
#include "Ognam/OgnamCharacter.h"

UBloodhoundClaws::UBloodhoundClaws()
{
	WeaponActionClass = UBloodhoundClawsAction::StaticClass();
	bInfiniteAmmo = true;
}

