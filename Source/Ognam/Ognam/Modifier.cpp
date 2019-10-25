// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "Modifier.h"
#include "OgnamCharacter.h"
#include "Ognam/OgnamMacro.h"
#include "UnrealNetwork.h"
#include "CoreNet.h"

UModifier::UModifier()
{
	SetIsReplicated(true);
}

void UModifier::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UModifier, ServerTimeStamp, COND_InitialOnly);
}

bool UModifier::ShouldEnd()
{
	return false;
}

void UModifier::TickModifier(float DeltaTime)
{
}

void UModifier::BeginPlay()
{
	Super::BeginPlay();

	if (!IsNetSimulating())
	{
		ServerTimeStamp = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
		ExecuteModifier();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UModifier::ExecuteModifier);
	}
}

void UModifier::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (!Target)
	{
		O_LOG_E(TEXT("Destroying Modifier that wasn't started"));
		return;
	}
	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		EndModifier();
	}
	Target->Modifiers.Remove(this);
}

EStatusEffect UModifier::GetStatusEffect() const
{
	return StatusEffect;
}

void UModifier::UpdateTimeStamp()
{
	ServerTimeStamp = GetWorld()->GetTimeSeconds();
}

void UModifier::BeginModifier()
{
}

void UModifier::EndModifier()
{
}

void UModifier::ExecuteModifier()
{
	if (ServerTimeStamp == 0)
	{
		O_LOG(TEXT("%s Server Time Stamp not delivered"), *GetClass()->GetName());
		ServerTimeStamp = GetWorld()->GetGameState()->GetServerWorldTimeSeconds();
	}
	Target = Cast<AOgnamCharacter>(GetOwner());
	if (!Target)
	{
		O_LOG_F(TEXT("Modifier applied to non-ognam character"));
		return;
	}
	if (StatusEffect != EStatusEffect::None)
	{
		Target->ApplyStatusEffect(StatusEffect);
	}

	BeginModifier();
	Target->Modifiers.Add(this);
}
