// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamWidgetComponent.h"
#include "UnrealNetwork.h"
#include "Blueprint/UserWidget.h"
#include "OgnamUserWidget.h"
#include "ConstructorHelpers.h"

UOgnamWidgetComponent::UOgnamWidgetComponent()
{
	bReplicates = true;
}

void UOgnamWidgetComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UOgnamWidgetComponent, OwningPlayerState);
}

void UOgnamWidgetComponent::SetOwningState_Implementation(APlayerState* State)
{
	OwningPlayerState = State;

	UOgnamUserWidget* OgnamWidget = Cast<UOgnamUserWidget>(GetUserWidgetObject());
	OgnamWidget->SetOwner(State);
}

APlayerState* UOgnamWidgetComponent::GetOwningState() const
{
	return OwningPlayerState;
}
