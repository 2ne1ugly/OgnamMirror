// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layton/Layton.h"
#include "LaytonClientLogin.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ULaytonClientLogin : public ULaytonClientLoginBase
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FMessageDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FMessageDelegate OnFailure;

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "Layton Client", meta = (WorldContext = "WorldContextObject"))
    static ULaytonClientLogin* LaytonClientLogin(UObject* WorldContextObject, const FString& Username);

    virtual void OnResponseReceived() override;
};
