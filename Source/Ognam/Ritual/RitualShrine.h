// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RitualShrine.generated.h"

UCLASS()
class OGNAM_API ARitualShrine : public AActor
{
	GENERATED_BODY()

	/*
	**	Components
	*/
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* CaptureField;

public:	
	ARitualShrine();

	/*
	**	Binded Function
	*/
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void Reset() override;

	UFUNCTION(NetMulticast, Reliable)
	void NetReset();
	void NetReset_Implmentation();

	UFUNCTION()
	void OnEnterField(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnExitField(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool ShouldRoundEnd() const;

	UFUNCTION(BlueprintCallable)
	float GetProgressPercent() const;

	UFUNCTION(BlueprintCallable)
	bool IsBeingCaptured() const;

protected:
	UPROPERTY(Transient)
	int32 DefenderCount;

	UPROPERTY(Transient)
	int32 AttackerCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ShrineName;

	/* How much faster the capture goes by for each additional attacker */
	UPROPERTY(Transient, EditAnywhere)
	float SpeedMultiplier;

	/* How long (in seconds) is needed to capture the point */
	UPROPERTY(EditAnywhere)
	float CaptureDuration;

	/* The current progress of the capture */
	UPROPERTY(Transient)
	float CaptureProgress;
};
