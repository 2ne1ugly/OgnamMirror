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
	UPROPERTY()
	class UUserWidget* HUD;

public:
	AOgnamPlayerController();

	/*
	**	Binded Functions
	*/
	virtual void BeginPlay() override;

	/*
	**	Exported Functions
	*/
	//Meant to be only called from server
	virtual void Die();

private:

	/*
	**	Props
	*/
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> HUDClass;
};
