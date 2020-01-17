// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamGameSlot.h"

UOgnamGameSlot::UOgnamGameSlot()
{

}

void UOgnamGameSlot::SetSession(FBlueprintSessionResult _Session)
{
	Session = _Session;
}

FBlueprintSessionResult UOgnamGameSlot::GetSession() const
{
	return Session;
}
