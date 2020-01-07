// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamStatics.h"
#include "OgnamEnum.h"
#include "OgnamPlayerstate.h"
#include "OgnamGameState.h"
#include "kismet/GameplayStatics.h"

bool UOgnamStatics::CanDamage(const UObject* WorldContextObject, AOgnamPlayerState* DamageInstigator, AOgnamPlayerState* Reciever, EDamageMethod DamageMethod)
{
	return Cast<AOgnamGameState>(UGameplayStatics::GetGameState(WorldContextObject))->CanDamage(DamageInstigator, Reciever, DamageMethod);
}

bool UOgnamStatics::CanDamage(const UObject* WorldContextObject, APawn* DamageInstigator, APawn* Reciever, EDamageMethod DamageMethod)
{
	AOgnamPlayerState* InstigatorPlayerState = DamageInstigator ? DamageInstigator->GetPlayerState<AOgnamPlayerState>() : nullptr;
	AOgnamPlayerState* RecieverPlayerState = Reciever ? Reciever->GetPlayerState<AOgnamPlayerState>() : nullptr;
	return Cast<AOgnamGameState>(UGameplayStatics::GetGameState(WorldContextObject))->CanDamage(InstigatorPlayerState, RecieverPlayerState, DamageMethod);
}
