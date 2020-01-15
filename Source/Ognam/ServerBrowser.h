// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "ServerBrowser.generated.h"


DECLARE_DELEGATE_OneParam(FServerBrowserCallback, TSharedPtr<FJsonObject>);

/**
 * 
 */
UCLASS()
class OGNAM_API UServerBrowser : public UObject
{
	GENERATED_BODY()

public:
	UServerBrowser();

	UFUNCTION(BlueprintCallable)
	void RegisterServer(int Port);

	void RegisterServerComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void GetServerList();

	void GetServerComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void UpdateServerInfo(int PlayerCount, FString Map, int Round);

	void UpdateServerInfoResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void Unregister();

	void UnregisterResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	int GetServerId() const;

	bool IsConnected() const;

private:
	class FHttpModule* Http;

	int ServerId;

	bool bConnected;
	
};
