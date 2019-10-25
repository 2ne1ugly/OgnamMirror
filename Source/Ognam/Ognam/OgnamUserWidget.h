// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OgnamUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UOgnamUserWidget : public UUserWidget
{
	GENERATED_BODY()

	UOgnamUserWidget(const FObjectInitializer& ObjectInitializer);

	class APlayerState* OwnerState;
	
public:
	void SetOwner(class APlayerState* OwnerState);

	UFUNCTION(BlueprintCallable)
	class APlayerState* GetOwnerState() const;
};
