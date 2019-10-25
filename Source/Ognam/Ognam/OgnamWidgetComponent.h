// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "OgnamWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UOgnamWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UOgnamWidgetComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(NetMulticast, Reliable)
	void SetOwningState(APlayerState* State);
	void SetOwningState_Implementation(APlayerState* State);

	class APlayerState* GetOwningState() const;

private:
	UPROPERTY(Replicated)
	class APlayerState* OwningPlayerState;


};
