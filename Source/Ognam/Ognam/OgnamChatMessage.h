// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OgnamChatMessage.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class OGNAM_API UOgnamChatMessage : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	class APlayerState* Sender;

	UPROPERTY(BlueprintReadOnly)
	FString Message;

	UFUNCTION(BlueprintCallable)
	FString GetFormattedMessage();
	
};
