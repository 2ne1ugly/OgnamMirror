// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ability.generated.h"

UENUM()
enum class EAbilityType : uint8
{
	None,
	Mobility,
	Unique,
	Utility,
	Special,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OGNAM_API UAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAbility();

	virtual bool IsNameStableForNetworking() const override;
	virtual bool IsSupportedForNetworking() const override;
	virtual void BeginPlay() override;

	//For UI
	UFUNCTION(BlueprintCallable)
	virtual bool ShouldShowNumber() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetNumber() const;

protected:
	/*
	**	Props
	*/
	UPROPERTY(VisibleAnywhere)
	class AOgnamCharacter* Target;

	UPROPERTY(VisibleAnywhere)
	EAbilityType AbilityType;
};
