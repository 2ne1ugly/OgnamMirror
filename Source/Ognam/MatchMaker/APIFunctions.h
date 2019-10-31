// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "APIFunctions.generated.h"


#define LOGIN "login"
#define JOIN_QUEUE "join_queue"
#define EXIT_QUEUE "exit_queue"
#define ACCEPT_GAME "accept_game"
#define GAME_FOUND "game_found"
#define GAME_CANCELLED "game_cancelled"
#define GAME_DETAILS "game_details"
#define FUNC "func"
#define SESSION_TOKEN "session_token"
#define REQUEST_TOKEN "request_token"
#define USERNAME "username"
#define PASSWORD "password"

USTRUCT()
struct OGNAM_API FAPIFunctions
{
	GENERATED_USTRUCT_BODY()

	static TSharedPtr<class FJsonObject> GetLogin(const FString Username, const FString Password, TSharedPtr<FString> RequestToken);

	static TSharedPtr<class FJsonObject>  GetJoinQueue(const FString SessionToken, TSharedPtr<FString> RequestToken);

	static TSharedPtr<class FJsonObject>  GetExitQueue(const FString SessionToken, TSharedPtr<FString> RequestToken);

	static TSharedPtr<class FJsonObject>  GetGameAccepted(const FString SessionToken, const bool bAccepted, TSharedPtr<FString> RequestToken);

	static TSharedPtr<class FJsonObject>  GetBaseObject(const FString Func, TSharedPtr<FString> RequestToken);

	static TSharedPtr<class FJsonObject>  GetBaseObjectWithSession(const FString SessionToken, const FString Func, TSharedPtr<FString> RequestToken);

	static FString CreateRequestToken();

	static FString GetJsonString(const TSharedRef<FJsonObject>& Object, bool bPrettyPrint = false);

	static bool SendJsonPacket(TSharedPtr<class FSocket> Sock, FString& Str);

};
