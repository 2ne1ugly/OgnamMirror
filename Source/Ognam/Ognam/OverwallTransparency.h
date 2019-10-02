// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OverwallTransparency.generated.h"

/*
**	Component for primitive components that needs to swap its material when blocking sight towards character.
**	This is done automatically.
**	Prob the best way to do this is to do it from ognam character if for performance.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OGNAM_API UOverwallTransparency : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOverwallTransparency();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddTargetComponent(UPrimitiveComponent* PrimitiveComponent, class UMaterialInterface* BlockingMaterial);

	void ComponentsBlocked();
	void ComponentsUnBlocked();
protected:
	bool IsActorInHitResults(TArray<FHitResult>& HitResults);

	UPROPERTY(EditAnywhere)
	TArray<UPrimitiveComponent*> TargetComponents;

	UPROPERTY(EditAnywhere)
	TArray<UMaterialInterface*> BlockingMaterials;
	TArray<UMaterialInterface*> SavedMaterials;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* DefaultMaterial;

	UPROPERTY()
	bool bBlocked;
};
