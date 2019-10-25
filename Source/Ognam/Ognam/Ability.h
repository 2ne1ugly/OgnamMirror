// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OgnamEnum.h"
#include "Ability.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OGNAM_API UAbility : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAbility();

	virtual bool IsSupportedForNetworking() const override;
	virtual void BeginPlay() override;

	//For UI
	UFUNCTION(BlueprintCallable)
	bool HasBegunPlay() const;

	UFUNCTION(BlueprintCallable)
	virtual bool ShouldShowNumber() const;

	UFUNCTION(BlueprintCallable)
	virtual float GetNumber() const;

protected:
	/*
	**	Props
	*/
	UPROPERTY(Transient, VisibleAnywhere)
	class AOgnamCharacter* Target;

	UPROPERTY(VisibleAnywhere)
	EAbilityType AbilityType;
};
