// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerBrowser.h"
#include "Ognam/OgnamMacro.h"

UServerBrowser::UServerBrowser()
{
	Http = &FHttpModule::Get();
}

void UServerBrowser::RegisterServer(int Port)
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UServerBrowser::RegisterServerComplete);
	Request->SetURL(FString::Printf(TEXT("http://localhost:5000/registerserver/%d"), Port));
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void UServerBrowser::RegisterServerComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	bConnected = bWasSuccessful;
	O_LOG(TEXT("%s"), *Response->GetContentAsString());
	ServerId = FCString::Atoi(*Response->GetContentAsString());
}

void UServerBrowser::GetServerList()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UServerBrowser::GetServerComplete);
	Request->SetURL(TEXT("http://localhost:5000/getservers/10"));
	Request->SetVerb("GET");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}


void UServerBrowser::GetServerComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	O_LOG(TEXT("%s"), *Response->GetContentAsString());
}

void UServerBrowser::UpdateServerInfo(int PlayerCount, FString Map, int Round)
{
	if (!bConnected)
	{
		return;
	}

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	FJsonObject Obj = FJsonObject();

	Obj.SetNumberField("player_count", PlayerCount);
	Obj.SetStringField("map_name", Map);
	Obj.SetNumberField("current_round", Round);

	FString Out;

	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out, 0);
	
	FJsonSerializer::Serialize(MakeShared<FJsonObject>(Obj), Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &UServerBrowser::UpdateServerInfoResponse);
	Request->SetURL(FString::Printf(TEXT("http://localhost:5000/updateserver/%d"), ServerId));
	Request->SetVerb("POST");
	Request->SetContentAsString(Out);
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void UServerBrowser::UpdateServerInfoResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	O_LOG(TEXT("%s"), *Response->GetContentAsString());
}

void UServerBrowser::Unregister()
{
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &UServerBrowser::GetServerComplete);
	Request->SetURL(FString::Printf(TEXT("http://localhost:5000/removeserver/%d"), ServerId));
	Request->SetVerb("GET");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}

void UServerBrowser::UnregisterResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	bConnected = !bWasSuccessful;
	O_LOG(TEXT("%s"), *Response->GetContentAsString());
}

bool UServerBrowser::IsConnected() const
{
	return bConnected;
}

int UServerBrowser::GetServerId() const
{
	return ServerId;
}