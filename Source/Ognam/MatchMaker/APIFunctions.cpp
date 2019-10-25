// Fill out your copyright notice in the Description page of Project Settings.


#include "APIFunctions.h"
#include "Json.h"
#include "JsonSerializer.h"
#include "JsonObject.h"

TSharedPtr<FJsonObject> FAPIFunctions::GetLogin(const FString Username, const FString Password, FString& RequestToken)
{
	TSharedPtr<FJsonObject> Object = GetBaseObject(LOGIN, RequestToken);
	Object->SetStringField(USERNAME, Username);
	Object->SetStringField(PASSWORD, Password);
	return Object;
}

TSharedPtr<FJsonObject> FAPIFunctions::GetJoinQueue(const FString SessionToken, FString& RequestToken)
{
	TSharedPtr<FJsonObject> Object = GetBaseObjectWithSession(SessionToken, JOIN_QUEUE, RequestToken);
	return Object;
}

TSharedPtr<FJsonObject> FAPIFunctions::GetExitQueue(const FString SessionToken, FString& RequestToken)
{
	TSharedPtr<FJsonObject> Object = GetBaseObjectWithSession(SessionToken, EXIT_QUEUE, RequestToken);
	return Object;
}

FString FAPIFunctions::CreateRequestToken()
{
	return FString("request_token");
}

TSharedPtr<FJsonObject> FAPIFunctions::GetBaseObject(const FString Func, FString& RequestToken)
{
	TSharedPtr<FJsonObject> Object = MakeShared <FJsonObject>();

	RequestToken = CreateRequestToken();
	Object->SetStringField(FUNC, Func);
	Object->SetStringField(REQUEST_TOKEN, RequestToken);

	return Object;
}

TSharedPtr<FJsonObject> FAPIFunctions::GetBaseObjectWithSession(const FString SessionToken, const FString Func, FString& RequestToken)
{
	TSharedPtr<FJsonObject> Object = GetBaseObject(Func, RequestToken);

	Object->SetStringField(SESSION_TOKEN, SessionToken);

	return Object;
}

FString FAPIFunctions::GetJsonString(TSharedRef<FJsonObject> Object, bool bPrettyPrint)
{
	FString Out;

	if (bPrettyPrint)
	{
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out, 0);
		FJsonSerializer::Serialize(Object, Writer);
	}
	else
	{
		TSharedRef<TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>> Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Out, 0);
		FJsonSerializer::Serialize(Object, Writer);
	}
	return Out;
}
