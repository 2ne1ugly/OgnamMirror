// Copyright 2019 Ognam Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "BloodhoundHuntingHourModifier.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundHuntingHourModifier : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UBloodhoundHuntingHourModifier();

	virtual bool ShouldEnd() override;

protected:
	virtual void BeginModifier() override;
	virtual void TickModifier(float DeltaTime) override;
	virtual void EndModifier() override;

protected:
	/*
	**	Protected
	*/
	float InitialRange;
	float Range;

	UFUNCTION(Client, Reliable)
	void ClientInformStalk(class AOgnamCharacter* Stalked);
	void ClientInformStalk_Implementation(class AOgnamCharacter* Stalked);

	UFUNCTION(Client, Reliable)
	void ClientStalkLost(class AOgnamCharacter* Character);
	void ClientStalkLost_Implementation(class AOgnamCharacter* Character);

	UPROPERTY(Transient)
	TSet<class AOgnamCharacter*> StalkedCharacters;

	class UMaterial* XRayMaterial;
};
