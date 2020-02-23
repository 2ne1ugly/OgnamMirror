// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layton/Layton.h"
#include "LaytonLobby.h"
#include "LaytonClientFindLobbies.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFindLobbiesDelegate, const TArray<ULaytonLobby*>&, Lobby);

/**
 * 
 */
UCLASS()
class OGNAM_API ULaytonClientFindLobbies : public ULaytonClientFindLobbiesBase
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FFindLobbiesDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FMessageDelegate OnFailure;

    UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, Category = "Layton Client", meta = (WorldContext = "WorldContextObject"))
    static ULaytonClientFindLobbies* LaytonClientFindLobbies(UObject* WorldContextObject);

    virtual void OnResponseReceived(bool Ok) override;
};
