// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OgnamPlayerController.h"
#include "OgnamControllerInterface.h"
#include "RitualPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ARitualPlayerController : public AOgnamPlayerController, public IOgnamControllerInterface
{
	GENERATED_BODY()

public:
	ARitualPlayerController();

	/*
	**	Binded Function
	*/
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	/*
	**	Interface Function
	*/
	virtual void OnPawnDeath() override;

	/*
	**	Exported Function
	*/
	UFUNCTION(BlueprintCallable)
	void ShowCharacterSelection();

	UFUNCTION(BlueprintCallable)
	void HideCharacterSelection();

protected:
	/*
	**	Internal Function
	*/
	void ToggleChangeCharacterUI();

	UFUNCTION(Server, WithValidation, Reliable)
	void ServerChangeCharacter(UClass* CharacterClass);
	bool ServerChangeCharacter_Validate(UClass* CharacterClass) { return true; };
	void ServerChangeCharacter_Implementation(UClass* CharacterClass);

	/*
	**	Props
	*/
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> CharacterSelectionHUDClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UUserWidget* CharacterSelectionHUD;
};
