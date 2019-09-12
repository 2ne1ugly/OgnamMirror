// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/OgnamCharacter.h"
#include "HereiraArrow.h"
#include "HereiraExplosiveArrow.h"
#include "Hereira.generated.h"

/**
 *	A Masked Woman
 */
UCLASS()
class OGNAM_API AHereira : public AOgnamCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UAudioComponent* ShotAudio;

public:
	AHereira();

	/*
	**	Binded Function
	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	**	Exported Function
	*/
	UFUNCTION(NetMulticast, Unreliable)
	void EndSprint();
	void EndSprint_Implementation();

protected:
	/*
	**	Abilities
	*/
	//Basic
	void FireArrow();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerFireArrow();
	bool ServerFireArrow_Validate() { return true; };
	void ServerFireArrow_Implementation();

	//Mobility
	void StartSprint();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerStartSprint();
	bool ServerStartSprint_Validate() { return true; };
	void ServerStartSprint_Implementation();

	void StopSprint();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerStopSprint();
	bool ServerStopSprint_Validate() { return true; };
	void ServerStopSprint_Implementation();

	//Unique
	void LoadExplosiveShot();

	UFUNCTION(Server, WithValidation, Unreliable)
	void ServerLoadExplosiveShot();
	bool ServerLoadExplosiveShot_Validate() { return true; };
	void ServerLoadExplosiveShot_Implementation();

	UFUNCTION(Client, Unreliable)
	void ClientFiredExplosiveShot();
	void ClientFiredExplosiveShot_Implementation();

	void Reload();

	UFUNCTION(Client, Unreliable)
	void FinishReload();
	void FinishReload_Implemenatation();

	//UFUNCTION(Server, WithValidation, Unrealiable)
	//void ServerReload();
	//bool ServerReload_Validate() { return true; };
	//void ServerReload_Implementaion();

	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	int32 NumArrows;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	int32 MaxArrows;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle BasicDelay;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle BasicReload;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle SprintCooldown;

	UPROPERTY(VisibleAnywhere, Category = Ability, BlueprintReadOnly)
	FTimerHandle ExplosiveShotCooldown;

	bool bReloading;
};
