// Fill out your copyright notice in the Description page of Project Settings.

#include "MaxwellAimDowned.h"
#include "Ognam/OgnamCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraComponent.h"
bool UMaxwellAimDowned::ShouldEnd()
{
	return bInterrupted;
}

void UMaxwellAimDowned::TickModifier(float DeltaTime)
{
	Target->Speed *= .5f;
}

void UMaxwellAimDowned::Interrupt()
{
	bInterrupted = true;
}

void UMaxwellAimDowned::BeginModifier()
{
	APlayerController* PlayerController = Target->GetController<APlayerController>();
	if (!PlayerController)
	{
		return;
	}
	UActorComponent* Camera = *Target->GetComponentsByTag(UCameraComponent::StaticClass(), TEXT("ADS")).begin();
	if (!Camera)
	{
		return;
	}
	Camera->SetActive(true);
	Target->Camera->SetActive(false);
}

void UMaxwellAimDowned::EndModifier()
{
	APlayerController* PlayerController = Target->GetController<APlayerController>();
	if (!PlayerController)
	{
		return;
	}
	UActorComponent* Camera = *Target->GetComponentsByTag(UCameraComponent::StaticClass(), TEXT("ADS")).begin();
	if (!Camera)
	{
		return;
	}
	Camera->SetActive(false);
	Target->Camera->SetActive(true);

}
