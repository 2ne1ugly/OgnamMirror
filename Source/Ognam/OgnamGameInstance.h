// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GrpcIncludesBegin.h"
#include "grpcpp/grpcpp.h"
#include "GrpcIncludesEnd.h"
#include "OgnamGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UOgnamGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UOgnamGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void SetPrefferedName(FString Name);

	UFUNCTION(BlueprintCallable)
	FString GetPrefferedName() const;

	UPROPERTY(BlueprintReadOnly)
	class ULaytonRpcClient* LaytonClient;

private:
	FString PrefferedName;
};
