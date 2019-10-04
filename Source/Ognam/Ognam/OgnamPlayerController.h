// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OgnamPlayerController.generated.h"

/**
 * 
 */
UCLASS(Config=OgnamGame)
class OGNAM_API AOgnamPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

public:
	AOgnamPlayerController();

	virtual void BeginPlay() override;
	virtual void OnPawnDeath();
	virtual void ClientRestart_Implementation(APawn* NewPawn) override;
	virtual void SetupInputComponent() override;

	UFUNCTION(Client, Unreliable)
	void ClientFeedBackDamageDealt(FVector Location, float Damage);
	void ClientFeedBackDamageDealt_Implementation(FVector Location, float Damage);

	UFUNCTION(Client, Unreliable)
	void ClientFeedBackKill();
	void ClientFeedBackKill_Implementation();

	UFUNCTION(exec)
	void ShowMenu();

	UFUNCTION(BlueprintCallable)
	float GetSensitivity() const;

	UFUNCTION(BlueprintCallable)
	void SetSensitivity(float Sens);

private:

	/*
	**	Props
	*/
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> OgnamHUDClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UUserWidget* OgnamHUD;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> MenuHUDClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UUserWidget* MenuHUD;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UUserWidget* CharacterHUD;

	UPROPERTY()
	class USoundCue* HitSound;

	UPROPERTY()
	class USoundCue* KillSound;
};
