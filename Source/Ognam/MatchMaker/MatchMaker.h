// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IPAddress.h"
#include "MatchMaker.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom))
class OGNAM_API UMatchMaker : public UObject
{
	GENERATED_BODY()

	UMatchMaker();
	
public:
	UFUNCTION(BlueprintCallable)
	void ConnectToServer();

	UFUNCTION()
	void ConnectedDelegate();

	UFUNCTION()
	void Connect();

	UFUNCTION(BlueprintCallable)
	bool IsConnecting() const;

	UFUNCTION(BlueprintCallable)
	bool IsConnected() const;

	UFUNCTION(BlueprintCallable)
	bool CheckIfAlive() const;

	UFUNCTION(BlueprintCallable)
	bool IsInQueue() const;

	UFUNCTION(BlueprintCallable)
	void Login(FString UserName, FString Password);

	void LoginResponse(TSharedPtr<class FJsonObject> Response);

	UFUNCTION(BlueprintCallable)
	void JoinQueue(/*map / gamemode*/);

	void JoinQueueResponse(TSharedPtr<class FJsonObject> Response);

	UFUNCTION(BlueprintCallable)
	void ExitQueue();

	/* */
	void ExitQueueResponse(TSharedPtr<class FJsonObject> Response);

	void GameFoundEvent(TSharedPtr<class FJsonObject> Response);

	UFUNCTION(BlueprintCallable)
	void GameFoundResponse(bool bAccepted);

	void GameReceiveDetails(TSharedPtr<class FJsonObject> Response);

private:
	class ISocketSubsystem* SocketSub;

	class FSocket* Sock;

	bool bIsConnected;
	bool bConnectionInProgress;

	bool bIsInQueue;

	/* If the Last sent request @see RequestToken is not retreived within this time, discard the request token and forget */
	float RequestTimeout = 10.f;

	/* The current session token, if it ever expires the client must re-login into the server */
	FString SessionToken;

	/* The most recently sent request. Used to ensure that the client is receiving the proper response */
	FString RequestToken;
	
	/* The time the RequestToken was last updated, used for timeout */
	long RequestSentTimestamp;
};
