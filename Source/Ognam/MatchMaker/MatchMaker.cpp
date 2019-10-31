// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "MatchMaker.h"
#include "SocketSubsystem.h"
#include "Sockets.h"
#include "Ognam/OgnamMacro.h"
#include "Async/Async.h"
#include "IPAddress.h"
#include "Dom/JsonObject.h"
#include "Json.h"
#include "JsonReader.h"
#include "JsonWriter.h"
#include "APIFunctions.h"
#include "JsonPrintPolicy.h"
#include "Policies/CondensedJsonPrintPolicy.h"
#include "Misc/Paths.h"

UMatchMaker::UMatchMaker()
{
	SocketSub = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	Sock = MakeShareable(SocketSub->CreateSocket(NAME_Stream, TEXT("Connection to Matchmaking server")));
}

void UMatchMaker::ConnectToServer()
{
	if (bIsConnected)
	{
		return;
	}
	Async(EAsyncExecution::TaskGraph, [&] {Connect(); }, [&] {ConnectedDelegate(); });
}

void UMatchMaker::Connect()
{
	if (!Sock.IsValid())
	{
		O_LOG(TEXT("Sock is null"));
		return;
	}
	bConnectionInProgress = true;
	TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	bool bIsValid;
	Addr->SetIp(TEXT("127.0.0.1"), bIsValid);
	Addr->SetPort(1337);
	Sock->Connect(*Addr);
}

void UMatchMaker::ConnectedDelegate()
{
	if (!Sock.IsValid())
	{
		O_LOG(TEXT("Sock is null"));
		return;
	}
	bConnectionInProgress = false;
	if (Sock->GetConnectionState() == ESocketConnectionState::SCS_Connected)
	{
		bIsConnected = true;
	}
	else
	{
		bIsConnected = false;
	}
	O_LOG(TEXT("Connection Complete, Success ? %s"), bIsConnected ? TEXT("Success") : TEXT("Failure"));

	// This should be moved to a tick-like function
	if (bIsConnected)
	{
		uint32 datasize;
		bool pending = Sock->HasPendingData(datasize);
		O_LOG(TEXT("pending data? %d : %d"), pending, datasize);
	}
}

bool UMatchMaker::IsConnecting() const
{
	return bConnectionInProgress;
}

bool UMatchMaker::IsConnected() const
{
	return bIsConnected;
}

bool UMatchMaker::CheckIfAlive() const
{
	return true;
}

bool UMatchMaker::IsInQueue() const
{
	return bIsInQueue;
}

void UMatchMaker::Login(FString UserName, FString Password)
{
	TSharedPtr<FJsonObject> Object = FAPIFunctions::GetLogin(UserName, Password, RequestToken);
	FString JsonStr = FAPIFunctions::GetJsonString(Object.ToSharedRef(), false);
	bool bSuccess = FAPIFunctions::SendJsonPacket(Sock, JsonStr);

	O_LOG(TEXT("Login Send %s"), bSuccess ? TEXT("SUCCESS") : TEXT("FAILURE"));
}

void UMatchMaker::LoginResponse(TSharedPtr<FJsonObject> Response)
{
}

void UMatchMaker::JoinQueue()
{
	TSharedPtr<FJsonObject> Object = FAPIFunctions::GetJoinQueue(SessionToken, RequestToken);
	FString JsonStr = FAPIFunctions::GetJsonString(Object.ToSharedRef(), false);
	bool bSuccess = FAPIFunctions::SendJsonPacket(Sock, JsonStr);

	O_LOG(TEXT("Login Send %s"), bSuccess ? TEXT("SUCCESS") : TEXT("FAILURE"));
}

void UMatchMaker::JoinQueueResponse(TSharedPtr<FJsonObject> Response)
{
}

void UMatchMaker::ExitQueue()
{
	TSharedPtr<FJsonObject> Object = FAPIFunctions::GetExitQueue(SessionToken, RequestToken);
	FString JsonStr = FAPIFunctions::GetJsonString(Object.ToSharedRef(), false);
	bool bSuccess = FAPIFunctions::SendJsonPacket(Sock, JsonStr);

	O_LOG(TEXT("Login Send %s"), bSuccess ? TEXT("SUCCESS") : TEXT("FAILURE"));
}

void UMatchMaker::ExitQueueResponse(TSharedPtr<FJsonObject> Response)
{
}

void UMatchMaker::GameFoundEvent(TSharedPtr<FJsonObject> Response)
{
}

void UMatchMaker::GameFoundResponse(bool bAccepted)
{
	TSharedPtr<FJsonObject> Object = FAPIFunctions::GetGameAccepted(SessionToken, bAccepted, RequestToken);
	FString JsonStr = FAPIFunctions::GetJsonString(Object.ToSharedRef(), false);
	bool bSuccess = FAPIFunctions::SendJsonPacket(Sock, JsonStr);

	O_LOG(TEXT("Login Send %s"), bSuccess ? TEXT("SUCCESS") : TEXT("FAILURE"));
}

void UMatchMaker::GameReceiveDetails(TSharedPtr<FJsonObject> Response)
{
}
