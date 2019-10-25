// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "Ability.h"
#include "OgnamCharacter.h"

UAbility::UAbility()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetNetAddressable();
	SetIsReplicated(true);
	bAutoRegister = true;
}

void UAbility::BeginPlay()
{
	Super::BeginPlay();
	Target = Cast<AOgnamCharacter>(GetOwner());
}

bool UAbility::HasBegunPlay() const
{
	return Target != nullptr;
}

bool UAbility::ShouldShowNumber() const
{
	return false;
}

float UAbility::GetNumber() const
{
	return 0.f;
}

bool UAbility::IsSupportedForNetworking() const
{
	return true;
}

