// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "Interfaces/Dispellable.h"
#include "AshaWhirlingBladesAction.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UAshaWhirlingBladesAction : public UActionModifier
{
	GENERATED_BODY()
	
public:
	UAshaWhirlingBladesAction();

	virtual void BeginPlay() override;

protected:
	//Server Call
	virtual void BeginPreDelay() override;
	virtual void BeginChannel() override;
	virtual void EndChannel() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* BoxTrigger;

	UPROPERTY(VisibleAnywhere)
		class UMaterial* DamageBoxMaterial;

	UPROPERTY(VisibleAnywhere)
		class UStaticMesh* DamageBoxMesh;

	TSet<APawn*> StrikedCharacters;
};
