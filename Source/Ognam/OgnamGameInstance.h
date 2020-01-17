// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
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

	UFUNCTION(BlueprintCallable)
	void SetPrefferedName(FString Name);

	UFUNCTION(BlueprintCallable)
	FString GetPrefferedName() const;

private:
	FString PrefferedName;

};
