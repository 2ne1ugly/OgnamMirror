// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamPlayerController.h"
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
	virtual void OnPawnDeath() override;
	virtual void Tick(float DeltaTime) override;

	/*
	**	Getters, Setters
	*/
	UFUNCTION(BlueprintCallable)
	float GetInteractionProgress() const;

	UFUNCTION(BlueprintCallable)
	class AActor* GetInteractedActor() const;

	UFUNCTION(BlueprintCallable)
	float GetDistanceBetweenInteracted() const;

	UFUNCTION(BlueprintCallable)
	bool IsInteracting() const;

	/*
	**	Exported Function
	*/
	UFUNCTION(BlueprintCallable)
	void ShowCharacterSelection();

	UFUNCTION(BlueprintCallable)
	void HideCharacterSelection();

	UFUNCTION(BlueprintCallable)
	bool CanInteract() const;

	UFUNCTION(BlueprintCallable)
	class AActor* GetTargetedActor() const;

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerStartInteract();
	bool ServerStartInteract_Validate() { return true; };
	void ServerStartInteract_Implementation();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerStopInteract();
	bool ServerStopInteract_Validate() { return true; };
	void ServerStopInteract_Implementation();

	void StartInteract();
	void StopInteract();

	UFUNCTION(Client, Reliable)
	void InterruptInteract();
	void InterruptInteract_Implementation();

protected:
	/*
	**	Internal Function
	*/
	void ToggleChangeCharacterUI();

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable)
	void ServerChangeCharacter(UClass* CharacterClass);
	bool ServerChangeCharacter_Validate(UClass* CharacterClass) { return true; };
	void ServerChangeCharacter_Implementation(UClass* CharacterClass);

	/*
	**	Props
	*/
	float InteractionTime;
	bool bIsInteracting;
	class AActor* InteractedActor;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> CharacterSelectionHUDClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UUserWidget* CharacterSelectionHUD;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> InteractionBarClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UUserWidget* InteractionBar;
};
