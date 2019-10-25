// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/ActionModifier.h"
#include "WeaponActionModifier.generated.h"

/**
 *	reusable Action modifier for weapons.
 *	Communicates with weapons for flow control.
 *	Slightly a dangerous class since it redefines ActionModifier a bit.
 *	Mostly server calls.
 */
UCLASS()
class OGNAM_API UWeaponActionModifier : public UActionModifier
{
	GENERATED_BODY()

public:
	UWeaponActionModifier();

	virtual bool ShouldEnd() override final;
	virtual void BeginModifier() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void ExecuteAction();	

	UFUNCTION(NetMulticast, Unreliable)
	void NetExecuteAciton();
	virtual void NetExecuteAciton_Implementation();


	void SetRepeat(bool Value);
	bool IsRunning() const;

protected:
	virtual void FinishPostDelay() override;

	UPROPERTY(Transient, EditAnywhere, Replicated)
	bool bRepeat;
};
