// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ognam/ExpirableModifier.h"
#include "BloodhoundStalking.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API UBloodhoundStalking : public UExpirableModifier
{
	GENERATED_BODY()

public:
	UBloodhoundStalking();

	virtual bool ShouldEnd() override;
	virtual void BeginModifier() override;
	virtual void TickModifier(float DeltaTime) override;
	virtual void EndModifier() override;

protected:
	UFUNCTION(Client, Reliable)
	void ClientInformStalk(const TArray<class AOgnamCharacter*>& Stalked);
	void ClientInformStalk_Implementation(const TArray<class AOgnamCharacter*>& Stalked);

	UFUNCTION(Client, Reliable)
	void ClientStalkLost(class AOgnamCharacter* Character);
	void ClientStalkLost_Implementation(class AOgnamCharacter* Character);

	UPROPERTY(Transient)
	TArray<class AOgnamCharacter*> StalkedCharacters;

	class UMaterial* XRayMaterial;

	float AquiringRange;
	float TickingRange;
};
