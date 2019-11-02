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
#include "Kismet/GameplayStatics.h"
#include "OgnamGameInstance.h"

UMatchMaker::UMatchMaker()
{
	SocketSub = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	Sock = MakeShareable(SocketSub->CreateSocket(NAME_Stream, TEXT("Connection to Matchmaking server")));

}

void UMatchMaker::Tick(float DeltaTime)
{
	FString Response;
	if (!ListenForResponse(Response))
	{
		return;
	}
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response);
	TSharedPtr<FJsonObject> Object;
	FJsonSerializer::Deserialize(Reader, Object);

	FString Function = Object->GetStringField("func");
	if (Function == LOGIN)
	{
		LoginResponse(Object);
	}
	else if (Function == JOIN_QUEUE)
	{
		JoinQueueResponse(Object);
	}
	else if (Function == EXIT_QUEUE)
	{
		ExitQueueResponse(Object);
	}
	else if (Function == GAME_FOUND)
	{
		GameFoundEvent(Object);
	}
	else if (Function == GAME_DETAILS)
	{
		GameReceiveDetails(Object);
	}
	else if (Function == GAME_CANCELLED)
	{
		GameCancelledEvent(Object);
	}
}

bool UMatchMaker::IsTickable() const
{
	return true;
}

TStatId UMatchMaker::GetStatId() const
{
	return GetStatID();
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

	O_LOG(TEXT("Join Send %s"), bSuccess ? TEXT("SUCCESS") : TEXT("FAILURE"));
}

void UMatchMaker::JoinQueueResponse(TSharedPtr<FJsonObject> Response)
{
}

void UMatchMaker::ExitQueue()
{
	TSharedPtr<FJsonObject> Object = FAPIFunctions::GetExitQueue(SessionToken, RequestToken);
	FString JsonStr = FAPIFunctions::GetJsonString(Object.ToSharedRef(), false);
	bool bSuccess = FAPIFunctions::SendJsonPacket(Sock, JsonStr);

	O_LOG(TEXT("Exit Send %s"), bSuccess ? TEXT("SUCCESS") : TEXT("FAILURE"));
}

void UMatchMaker::ExitQueueResponse(TSharedPtr<FJsonObject> Response)
{
}

void UMatchMaker::GameCancelledEvent(TSharedPtr<FJsonObject> Response)
{
	bGameFound = false;
	bWaitingToStart = false;
	O_LOG(TEXT("Game cancelled!"));
}

void UMatchMaker::GameFoundEvent(TSharedPtr<FJsonObject> Response)
{
	bGameFound = true;

	GameAcceptToken = Response->GetStringField(REQUEST_TOKEN);
}

void UMatchMaker::GameFoundResponse(bool bAccepted)
{
	bGameFound = false;
	bWaitingToStart = true;
	TSharedPtr<FJsonObject> Object = FAPIFunctions::GetGameAccepted(SessionToken, bAccepted, MakeShared<FString>(GameAcceptToken));
	FString JsonStr = FAPIFunctions::GetJsonString(Object.ToSharedRef(), false);
	bool bSuccess = FAPIFunctions::SendJsonPacket(Sock, JsonStr);

	O_LOG(TEXT("GameFound Send %s"), bSuccess ? TEXT("SUCCESS") : TEXT("FAILURE"));
}

void UMatchMaker::GameReceiveDetails(TSharedPtr<FJsonObject> Response)
{
	O_LOG(TEXT("Time to start! %s"), *Response->GetStringField("connection_string"));

	APlayerController* PC = GameInstance->GetWorld()->GetFirstPlayerController();

	if (!PC)
	{
		O_LOG(TEXT("controller is null"));
	}
	

	PC->ClientTravel(Response->GetStringField("connection_string"), ETravelType::TRAVEL_Absolute);
}

bool UMatchMaker::ListenForResponse(FString& Response)
{
	uint32 DataSize;
	if (!Sock->HasPendingData(DataSize))
	{
		return false;
	}
	uint8 Header[4] = { 0 };
	int32 Bread;
	Sock->Recv(Header, 4, Bread);
	FMemory::Memcpy(&DataSize, Header, 4);
	O_LOG(TEXT("Incoming Size: %d\n"), DataSize);
	TArray<uint8> Data;
	Data.SetNum(DataSize);
	Sock->Recv(Data.GetData(), DataSize, Bread);
	for (int32 i = 0; i < Bread; i++)
	{
		Data[i]--;
	}
	Response = BytesToString(Data.GetData(), Bread);
	O_LOG(TEXT("%s"), *Response);
	return true;
}

void UMatchMaker::SetGameInstance(UOgnamGameInstance* Instance)
{
	GameInstance = Instance;
}
