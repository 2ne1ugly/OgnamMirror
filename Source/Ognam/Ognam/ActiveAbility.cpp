// Fill out your copyright notice in the Description page of Project Settings.

#include "ActiveAbility.h"
#include "OgnamCharacter.h"
#include "Components/InputComponent.h"

UActiveAbility::UActiveAbility()
{
}

void UActiveAbility::BeginPlay()
{
	Super::BeginPlay();

	switch (AbilityType)
	{
	case EAbilityType::Mobility:
		ButtonPressed = &Target->OnMobilityPressed;
		ButtonReleased = &Target->OnMobilityReleased;
		break;
	case EAbilityType::Unique:
		ButtonPressed = &Target->OnUniquePressed;
		ButtonReleased = &Target->OnUniqueReleased;
		break;
	case EAbilityType::Utility:
		ButtonPressed = &Target->OnUtilityPressed;
		ButtonReleased = &Target->OnUtilityReleased;
		break;
	case EAbilityType::Special:
		ButtonPressed = &Target->OnSpecialPressed;
		ButtonReleased = &Target->OnSpecialReleased;
		break;
	default:
		break;
	}

	ButtonPressed->AddUObject(this, &UActiveAbility::OnButtonPressed);
	ButtonReleased->AddUObject(this, &UActiveAbility::OnButtonReleased);
}

void UActiveAbility::OnButtonPressed()
{
}

void UActiveAbility::OnButtonReleased()
{
}

void UActiveAbility::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ButtonPressed->Remove(PressHandle);
	ButtonReleased->Remove(ReleaseHandle);

}
