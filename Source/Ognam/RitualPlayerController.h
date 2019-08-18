// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OgnamPlayerController.h"
#include "RitualPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ARitualPlayerController : public AOgnamPlayerController
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
	**	Overritten Function
	*/
	virtual void Die() override;
	virtual void ServerChangeCharacter_Implementation(UClass* Character);

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

	/*
	**	Props
	*/
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> CharacterSelectionHUDClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UUserWidget* CharacterSelectionHUD;
};
