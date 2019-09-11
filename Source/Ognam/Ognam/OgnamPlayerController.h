// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OgnamPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API AOgnamPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	/*
	**	Widgets
	*/

public:
	AOgnamPlayerController();

	/*
	**	Binded Functions
	*/
	virtual void BeginPlay() override;
	virtual void OnPawnDeath();
	virtual void ClientRestart_Implementation(APawn* NewPawn) override;

private:

	/*
	**	Props
	*/
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> OgnamHUDClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UUserWidget* OgnamHUD;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UUserWidget* CharacterHUD;

};
