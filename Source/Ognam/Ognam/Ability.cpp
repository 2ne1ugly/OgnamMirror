// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "Ability.h"
#include "OgnamCharacter.h"

UAbility::UAbility()
{
	SetNetAddressable();
	SetIsReplicated(true);
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

UTexture2D *UAbility::GetIcon() const
{
	return Icon;
}

bool UAbility::IsSupportedForNetworking() const
{
	return true;
}

