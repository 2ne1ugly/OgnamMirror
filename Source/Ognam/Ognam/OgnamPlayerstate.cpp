// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamPlayerState.h"
#include "UnrealNetwork.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "OgnamPlayerController.h"
#include "Ognam/OgnamMacro.h"
#include "Ognam/OgnamCharacter.h"
#include "Characters/Hereira/Hereira.h"

AOgnamPlayerState::AOgnamPlayerState()
{
	NumKill = 0;
	NumDeath = 0;
	Team = TEXT("No Team");
	bIsAlive = true;
	SelectedPawnClass = AHereira::StaticClass();
}

void AOgnamPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AOgnamPlayerState, NumKill);
	DOREPLIFETIME(AOgnamPlayerState, NumDeath);
	DOREPLIFETIME(AOgnamPlayerState, Team);
	DOREPLIFETIME(AOgnamPlayerState, bIsAlive);
}

void AOgnamPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
	if (PlayerState)
	{
		AOgnamPlayerState* OgnamPlayerState = Cast<AOgnamPlayerState>(PlayerState);
		if (OgnamPlayerState)
		{
		}
	}
}

void AOgnamPlayerState::OverrideWith(APlayerState* PlayerState)
{
	Super::OverrideWith(PlayerState);
	if (PlayerState)
	{
		AOgnamPlayerState* OgnamPlayerState = Cast<AOgnamPlayerState>(PlayerState);
		if (OgnamPlayerState)
		{
		}
	}
}

void AOgnamPlayerState::NotifyDamageDealt(AActor* DamageCauser, AActor* DamageReciever, AController* DamageInstigator, AController* RecieverController, float Damage)
{
	AOgnamPlayerController* OgnamController = Cast<AOgnamPlayerController>(DamageInstigator);
	if (!OgnamController)
	{
		O_LOG(TEXT("Not Ognam controller"));
		return;
	}
	OgnamController->ClientFeedbackDamageDealt(DamageCauser, DamageReciever, DamageReciever->GetActorLocation(), Damage);
}

void AOgnamPlayerState::NotifyDamageRecieved(AActor* DamageCauser, AActor* DamageReciever, AController* DamageInstigator, AController* RecieverController, float Damage)
{
	AOgnamPlayerController* OgnamController = Cast<AOgnamPlayerController>(RecieverController);
	if (!OgnamController)
	{
		O_LOG(TEXT("Not Ognam controller"));
		return;
	}
	OgnamController->ClientFeedbackDamageRecieved(DamageReciever, DamageReciever, DamageReciever->GetActorLocation(), Damage);
}

void AOgnamPlayerState::NotifyKill(AActor* Causer, AActor* Reciever, AController* KillInstigator, AController* RecieverController)
{
	//Increase kill only when killed ognam character
	if (Cast<AOgnamCharacter>(Reciever))
	{
		NumKill++;
		AOgnamPlayerController* PlayerController = Cast<AOgnamPlayerController>(KillInstigator);
		if (!PlayerController)
		{
			O_LOG(TEXT("Not Ognam controller"));
		}
		else
		{
			PlayerController->ClientFeedbackKill(Causer, Reciever);
		}
	}
}

void AOgnamPlayerState::NotifyDeath(AActor* Causer, AActor* Reciever, AController* DeathInstigator, AController* RecieverController)
{
	NumDeath++;
	AOgnamPlayerController* PlayerController = Cast<AOgnamPlayerController>(RecieverController);
	if (!PlayerController)
	{
		O_LOG(TEXT("Not Ognam controller"));
	}
	else
	{
		PlayerController->ClientFeedbackDeath(Causer, Reciever);
	}
}

void AOgnamPlayerState::SetTeam(FName name)
{
	Team = name;
}

FName AOgnamPlayerState::GetTeam() const
{
	return Team;
}

void AOgnamPlayerState::SetIsAlive(bool Value)
{
	bIsAlive = Value;
}

bool AOgnamPlayerState::IsAlive() const
{
	return bIsAlive;
}

UClass* AOgnamPlayerState::GetSelectedPawnClass() const
{
	return SelectedPawnClass;
}

void AOgnamPlayerState::NetReceiveMessage_Implementation(const FString& Message, APlayerState* Sender)
{
	if (GEngine->GetFirstLocalPlayerController(GetWorld()) &&
		GEngine->GetFirstLocalPlayerController(GetWorld())->GetPlayerState<APlayerState>() != Sender)
	{
		DisplayMessage(Message, Sender);
	}
}

void AOgnamPlayerState::ServerSendMessage_Implementation(const FString& Message)
{
	NetReceiveMessage(Message, this);
}

void AOgnamPlayerState::DisplayMessage(const FString& Message, APlayerState* Sender)
{
	GEngine->AddOnScreenDebugMessage(-1, 60.f, FColor::Red, FString::Printf(TEXT("%s: %s"), *Sender->GetPlayerName(), *Message));
}

UClass* AOgnamPlayerState::GetPawnClass() const
{
	return PawnClass;
}

void AOgnamPlayerState::SetPawnClass(UClass* Pawn)
{
	PawnClass = Pawn;
}

void AOgnamPlayerState::SetSelectedPawnClass(UClass* Pawn)
{
	SelectedPawnClass = Pawn;
}