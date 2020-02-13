// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameInstance.h"
//#include "OnlineSessionSettings.h"
#include "Engine.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include "Ognam/OgnamMacro.h"

#include "GrpcIncludesBegin.h"
#include "grpcpp/create_channel.h"
#include "GrpcIncludesEnd.h"
//#include "Layton.h"

UOgnamGameInstance::UOgnamGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

FString UOgnamGameInstance::GetPrefferedName() const
{
	return "NONE";
}

void UOgnamGameInstance::Init()
{

	grpc::CreateChannel("", nullptr);
	//LaytonClient = NewObject<ULaytonRpcClient>(this);
	//LaytonClient->Init("10.10.151.75:50051", UChannelCredentials::MakeInsecureChannelCredentials());
}

void UOgnamGameInstance::SetPrefferedName(FString Name)
{
	PrefferedName = Name;
}
