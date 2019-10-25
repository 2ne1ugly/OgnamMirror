// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "BloodhoundClaws.h"
#include "BloodhoundClawsAction.h"
#include "Ognam/OgnamCharacter.h"

UBloodhoundClaws::UBloodhoundClaws()
{
	WeaponActionClass = UBloodhoundClawsAction::StaticClass();
	bInfiniteAmmo = true;
}

