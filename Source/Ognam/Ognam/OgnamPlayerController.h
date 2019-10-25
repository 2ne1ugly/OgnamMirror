// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OgnamPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnChatTrigger);

/**
 * 
 */
UCLASS()
class OGNAM_API AOgnamPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

public:
	AOgnamPlayerController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ClientRestart_Implementation(APawn* NewPawn) override;
	virtual void SetupInputComponent() override;
	virtual void ReceivedPlayer() override;
	virtual void OnRep_PlayerState() override;

	UFUNCTION(Client, Unreliable)
	void ClientFeedbackDamageDealt(AActor* Causer, AActor* Reciever, FVector Location, float Damage);
	void ClientFeedbackDamageDealt_Implementation(AActor* Causer, AActor* Reciever, FVector Location, float Damage);

	UFUNCTION(Client, Unreliable)
	void ClientFeedbackDamageRecieved(AActor* Causer, AActor* Reciever, FVector Location, float Damage);
	void ClientFeedbackDamageRecieved_Implementation(AActor* Causer, AActor* Reciever, FVector Location, float Damage);

	UFUNCTION(Client, Unreliable)
	void ClientFeedbackKill(AActor* Causer, AActor* Reciever);
	void ClientFeedbackKill_Implementation(AActor* Causer, AActor* Reciever);

	UFUNCTION(Client, Unreliable)
	void ClientFeedbackDeath(AActor* Causer, AActor* Reciever);
	void ClientFeedbackDeath_Implementation(AActor* Causer, AActor* Reciever);

	UFUNCTION(exec)
	void ShowMenu();

	UFUNCTION(BlueprintCallable)
	float GetSensitivity() const;

	UFUNCTION(BlueprintCallable)
	void SetSensitivity(float Sens);

	UFUNCTION(BlueprintCallable)
	void JoinGame(FString Address);

	UFUNCTION(Client, Reliable)
	void ClientGameStarted();
	void ClientGameStarted_Implementation();

	UFUNCTION(Server, Reliable)
	void ServerSendName(const FString& Name);
	void ServerSendName_Implementation(const FString& Name);

	UFUNCTION(exec, BlueprintCallable)
	void SendMessage(FString Message);

	void ShowGameInfo();
	void HideGameInfo();

	void ChatTrigger();

	void Release();

	UPROPERTY(BlueprintAssignable)
	FOnChatTrigger OnChatTrigger;

	UPROPERTY(BlueprintAssignable)
	FOnChatTrigger OnChatRelease;

	UFUNCTION(BlueprintCallable)
	void RequestMouseControl();

	UFUNCTION(BlueprintCallable)
	void ReleaseMouseControl();

	UFUNCTION(BlueprintCallable)
	void LockPlayerInput();

	UFUNCTION(BlueprintCallable)
	void UnlockPlayerInput();

	UFUNCTION(BlueprintCallable)
	void RequestCompleteLock();

	UFUNCTION(BlueprintCallable)
	void ReleaseCompleteLock();

	UFUNCTION(BlueprintCallable)
	bool IsInMainMenu() const;

	UFUNCTION(BlueprintCallable)
	void SetIsInMainMenu(bool bInMenu);

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
	TSubclassOf<class UUserWidget> GameInfoHUDClass;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UUserWidget* GameInfoHUD;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	class UUserWidget* CharacterHUD;

	UPROPERTY()
	class USoundCue* HitSound;

	UPROPERTY()
	class USoundCue* KillSound;

	int32 MouseControl;

	int32 InputControl;

	bool bIsInMainMenu;
};
