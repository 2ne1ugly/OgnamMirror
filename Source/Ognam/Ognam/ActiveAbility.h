// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "OgnamCharacter.h"
#include "ActiveAbility.generated.h"

/**
 *	Ability That reacts to button presses and releases.
 */
UCLASS()
class OGNAM_API UActiveAbility : public UAbility
{
	GENERATED_BODY()

public:
	UActiveAbility();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnButtonPressed();
	UFUNCTION()
	virtual void OnButtonReleased();

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	AOgnamCharacter::FActionDelegate* ButtonPressed;
	AOgnamCharacter::FActionDelegate* ButtonReleased;

	FDelegateHandle PressHandle;
	FDelegateHandle ReleaseHandle;
};
