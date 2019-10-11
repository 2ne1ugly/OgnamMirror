// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameState.h"
#include "OgnamMacro.h"
#include "OgnamPlayerState.h"
#include "OgnamCharacter.h"
#include "Subsystem.h"
#include "OnlineSubsystem.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

AOgnamGameState::AOgnamGameState()
{
}

void AOgnamGameState::BeginPlay()
{
	Super::BeginPlay();

	bool bCanBind;
	TSharedRef<FInternetAddr> LocalIP = ISocketSubsystem::Get()->GetLocalHostAddr(*GLog, bCanBind);
	ServerAddress = FString::Printf(TEXT("%s:%d"), *(LocalIP->ToString(false)), GetWorld()->URL.Port);
}

void AOgnamGameState::NotifyDamageEvent(AActor* DamageCauser, AActor* DamageReciever, AController* DamageInstigator, AController* RecieverController, float Damage)
{
	check(DamageCauser && DamageReciever);
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
	check(Causer && Reciever);
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
