// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OverwallHidden.generated.h"

/*
**	Component for scene components that should be hidden when looking through walls
**	This is done automatically.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OGNAM_API UOverwallHidden : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOverwallHidden();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void HideComponents();
	void ShowComponents();
	void AddTargetComponents(USceneComponent* SceneComponent);

protected:
	UPROPERTY(VisibleAnywhere)
	TArray<USceneComponent*> TargetComponents;

	UPROPERTY()
	bool bOverwallHidden;
};
