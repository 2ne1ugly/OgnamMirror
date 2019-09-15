// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OGNAM_API UWeapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeapon();

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;
	virtual bool IsSupportedForNetworking() const override;	

protected:
	virtual void BasicPressed();
	virtual void BasicReleased();

	UPROPERTY(VisibleAnywhere)
	class AOgnamCharacter* Target;

	FDelegateHandle BasicPressHandle;
	FDelegateHandle BasicReleaseHandle;
};
