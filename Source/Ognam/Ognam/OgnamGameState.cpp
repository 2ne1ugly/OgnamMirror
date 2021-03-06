// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameState.h"
#include "BreakableStructure.h"
#include "OgnamMacro.h"
#include "OgnamPlayerState.h"
#include "OgnamCharacter.h"
#include "KillFeed.h"
#include "Subsystem.h"
#include "OnlineSubsystem.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "UnrealNetwork.h"
#include "TimerManager.h"
#include "OgnamPlayerController.h"
#include "OgnamChatMessage.h"

AOgnamGameState::AOgnamGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOgnamGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RemoveFromKillFeed();
	ChatVisibleLifetime -= DeltaTime;
}

void AOgnamGameState::BeginPlay()
{
	Super::BeginPlay();

	bool bCanBind;
	if (HasAuthority())
	{
		TSharedRef<FInternetAddr> LocalIP = ISocketSubsystem::Get()->GetLocalHostAddr(*GLog, bCanBind);
		ServerAddress = FString::Printf(TEXT("%s:%d"), *(LocalIP->ToString(false)), GetWorld()->URL.Port);
	}
}

void AOgnamGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamGameState, ServerAddress);
	//DOREPLIFETIME(AOgnamGameState, KillFeed);
}

void AOgnamGameState::NotifyDamageEvent(AActor* DamageCauser, AActor* DamageReciever, AController* DamageInstigator, AController* RecieverController, float Damage)
{
	AOgnamPlayerState* InstigatorPlayerState = nullptr;
	AOgnamPlayerState* RecieverPlayerState = nullptr;
	//Try getting both player states.
	if (DamageInstigator)
	{
		InstigatorPlayerState = DamageInstigator->GetPlayerState<AOgnamPlayerState>();
	}
	if (RecieverController)
	{
		RecieverPlayerState = RecieverController->GetPlayerState<AOgnamPlayerState>();
	}

	//Send events to both states.
	if (InstigatorPlayerState)
	{
		InstigatorPlayerState->NotifyDamageDealt(DamageCauser, DamageReciever, DamageInstigator, RecieverController, Damage);
	}
	if (RecieverPlayerState)
	{
		RecieverPlayerState->NotifyDamageRecieved(DamageCauser, DamageReciever, DamageInstigator, RecieverController, Damage);
	}
}

void AOgnamGameState::NotifyKillEvent(AActor* Causer, AActor* Reciever, AController* KillInstigator, AController* RecieverController)
{
	AOgnamPlayerState* InstigatorPlayerState = nullptr;
	AOgnamPlayerState* RecieverPlayerState = nullptr;

	//Try getting both player states.
	if (KillInstigator)
	{
		InstigatorPlayerState = KillInstigator->GetPlayerState<AOgnamPlayerState>();
	}
	if (RecieverController)
	{
		RecieverPlayerState = RecieverController->GetPlayerState<AOgnamPlayerState>();
	}

	if (InstigatorPlayerState && RecieverPlayerState)
	{
		AddPlayerKilled(InstigatorPlayerState, RecieverPlayerState);
	}

	//Send events to both states.
	if (InstigatorPlayerState)
	{
		InstigatorPlayerState->NotifyKill(Causer, Reciever, KillInstigator, RecieverController);
	}
	if (RecieverPlayerState)
	{
		RecieverPlayerState->NotifyDeath(Causer, Reciever, KillInstigator, RecieverController);
	}
}

FString AOgnamGameState::GetServerIP() const
{
	return ServerAddress;
}

void AOgnamGameState::AddPlayerKilled_Implementation(AOgnamPlayerState* Killer, AOgnamPlayerState* Receiver)
{
	UKillFeed* Feed = NewObject<UKillFeed>(this);

	Feed->Killer = Killer;
	Feed->Receiver = Receiver;
	GetWorld()->GetTimerManager().SetTimer(Feed->LifetimeHandle, Feed->LifetimeDuration, false);
	KillFeed.Add(Feed);
}

void AOgnamGameState::RemoveFromKillFeed()
{
	for (int32 i = KillFeed.Num() - 1; i >= 0; i--)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(KillFeed[i]->LifetimeHandle))
		{
			UKillFeed* Feed = KillFeed[i];
			KillFeed.RemoveAt(i);
		}
	}
}

void AOgnamGameState::NetReceiveMessage_Implementation(const FString& Message, APlayerState* Sender)
{
	DisplayMessage(Message, Sender);
}

void AOgnamGameState::DisplayMessage(const FString& Message, APlayerState* Sender)
{
	UOgnamChatMessage* ChatMessage = NewObject<UOgnamChatMessage>(Sender);
	ChatMessage->Sender = Sender;
	ChatMessage->Message = Message;
	Messages.Add(ChatMessage);
	ChatVisibleLifetime = 20.f;
	bChatDirty = true;
}

void AOgnamGameState::NetReset_Implementation()
{
	for (TActorIterator<ABreakableStructure> Itr(GetWorld()); Itr; ++Itr)
	{
		Itr->Reset();
	}
}

bool AOgnamGameState::CanDamage(AOgnamPlayerState* DamageInstigator, AOgnamPlayerState* Reciever, EDamageMethod DamageMethod) const
{
	//if (!DamageInstigator || !Reciever)
	//{
	//	return false;
	//}

	if (!DamageInstigator)
	{
		return false;
	}

	if (!Reciever && (DamageMethod & EDamageMethod::DamagesEnemy) != EDamageMethod::None)
	{
		return true;
	}

	if (DamageInstigator->GetTeam() != Reciever->GetTeam() &&
		(DamageMethod & EDamageMethod::DamagesEnemy) != EDamageMethod::None)
	{
		return true;
	}

	if (DamageInstigator != Reciever &&
		DamageInstigator->GetTeam() == Reciever->GetTeam() &&
		(DamageMethod & EDamageMethod::DamagesAlly) != EDamageMethod::None)
	{
		return true;
	}

	if (DamageInstigator == Reciever &&
		(DamageMethod & EDamageMethod::DamagesSelf) != EDamageMethod::None)
	{
		return true;
	}
	return false;
}
