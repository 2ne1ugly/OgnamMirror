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

	/*
	**	Exported Functions
	*/
	//Meant to be only called from server
	virtual void Die();

	//Ask server to change character
	UFUNCTION(Server, Reliable, BlueprintCallable, WithValidation)
	void ServerChangeCharacter(UClass* PawnClass);
	virtual bool ServerChangeCharacter_Validate(UClass* PawnClass) { return true; };
	virtual void ServerChangeCharacter_Implementation(UClass* PawnClass);

private:

	/*
	**	Props
	*/
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> OgnamHUDClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UUserWidget* OgnamHUD;

};
