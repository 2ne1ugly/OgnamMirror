// Fill out your copyright notice in the Description page of Project Settings.


#include "OgnamUserWidget.h"
#include "UnrealNetwork.h"

UOgnamUserWidget::UOgnamUserWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UOgnamUserWidget::SetOwner(class APlayerState* InOwnerState)
{
	OwnerState = InOwnerState;
}

APlayerState* UOgnamUserWidget::GetOwnerState() const
{
	return OwnerState;
}
