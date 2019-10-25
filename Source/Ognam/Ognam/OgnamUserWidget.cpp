// Copyright 2019 Ognam Studios. All Rights Reserved.

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
