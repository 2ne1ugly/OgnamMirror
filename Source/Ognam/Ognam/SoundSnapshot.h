// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundSnapshot.generated.h"

UCLASS()
class OGNAM_API ASoundSnapshot : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	class UPoseableMeshComponent* Mesh;

public:	
	// Sets default values for this actor's properties
	ASoundSnapshot();

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void Snapshot(USkeletalMeshComponent* SkeletalMesh);

protected:
	UPROPERTY(VisibleAnywhere)
	UMaterial* SnapshotMaterial;

	UPROPERTY(VisibleAnywhere)
	UMaterialInstanceDynamic* SnapshotDynamicMaterial;
};
