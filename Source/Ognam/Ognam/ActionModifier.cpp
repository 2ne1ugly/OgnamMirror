// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionModifier.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "OgnamCharacter.h"
#include "Ognam/OgnamMacro.h"
#include "UnrealNetwork.h"

UActionModifier::UActionModifier()
{
	Stage = EActionStage::PreAction;
	PreDelayDuration = 0.f;
	ChannelDuration = 1.f;
	PostDelayDuration = 0.f;
}

void UActionModifier::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UActionModifier, bInterrupted);
}

bool UActionModifier::ShouldEnd()
{
	return bInterrupted || Stage == EActionStage::PostAction;
}

void UActionModifier::TickModifier(float DeltaTime)
{
	switch (Stage)
	{
	case EActionStage::PreAction:
		break;
	case EActionStage::PreDelay:
		TickPreDelay(DeltaTime);
		break;
	case EActionStage::Channel:
		TickChannel(DeltaTime);
		break;
	case EActionStage::PostDelay:
		TickPostDelay(DeltaTime);
		break;
	case EActionStage::PostAction:
		O_LOG(TEXT("Ticks on post action"));
		break;
	default:
		O_LOG(TEXT("Unknown action stage"));
		break;
	}
}

EActionStage UActionModifier::GetStage() const
{
	return Stage;
}

void UActionModifier::BeginModifier()
{
	ExecutePreDelay();
}

void UActionModifier::EndModifier()
{
	if (Stage != EActionStage::PostAction)
	{
		if (bInterrupted)
		{
			Interrupt();
		}
		else
		{
			switch (Stage)
			{
			case EActionStage::PreDelay:
				EndPreDelay();
				BeginChannel();
			case EActionStage::Channel:
				EndChannel();
				BeginPostDelay();
			case EActionStage::PostDelay:
				EndPostDelay();
			default:
				Stage = EActionStage::PostAction;
			}
		}
	}
}

void UActionModifier::ExecutePreDelay()
{
	Stage = EActionStage::PreDelay;
	SetStatusEffect(PreDelayStatusEffect);
	if (PreDelayAction != EActionNotifier::None)
	{
		Target->TakeAction(PreDelayAction);
	}
	BeginPreDelay();

	if (PreDelayDuration == 0)
	{
		FinishPreDelay();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(PreDelayTimer, this, &UActionModifier::FinishPreDelay, PreDelayDuration, false);
	}
}

void UActionModifier::BeginPreDelay()
{
}

void UActionModifier::TickPreDelay(float DeltaTime)
{
}

void UActionModifier::EndPreDelay()
{
}

void UActionModifier::FinishPreDelay()
{
	EndPreDelay();
	ExecuteChannel();
}

void UActionModifier::ExecuteChannel()
{
	Stage = EActionStage::Channel;
	SetStatusEffect(ChannelStatusEffect);
	if (ChannelAction != EActionNotifier::None)
	{
		Target->TakeAction(ChannelAction);
	}
	BeginChannel();

	if (ChannelDuration == 0.f)
	{
		FinishChannel();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(ChannelTimer, this, &UActionModifier::FinishChannel, ChannelDuration, false);
	}
}

void UActionModifier::BeginChannel()
{
}

void UActionModifier::TickChannel(float DeltaTime)
{
}

void UActionModifier::EndChannel()
{
}

void UActionModifier::FinishChannel()
{
	EndChannel();
	ExecutePostDelay();
}

void UActionModifier::ExecutePostDelay()
{
	Stage = EActionStage::PostDelay;
	SetStatusEffect(PostDelayStatusEffect);
	if (PostDelayAction != EActionNotifier::None)
	{
		Target->TakeAction(PostDelayAction);
	}
	BeginPostDelay();

	//Compensate server lag;
	if (PostDelayDuration == 0)
	{
		FinishPostDelay();
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(PostDelayTimer, this, &UActionModifier::FinishPostDelay, PostDelayDuration, false);
	}
}

void UActionModifier::BeginPostDelay()
{
}

void UActionModifier::TickPostDelay(float DeltaTime)
{
}

void UActionModifier::EndPostDelay()
{
}

void UActionModifier::FinishPostDelay()
{
	EndPostDelay();
	Stage = EActionStage::PostAction;
}

void UActionModifier::Interrupt()
{
	bInterrupted = true;
	switch (Stage)
	{
	case EActionStage::PreAction:
	case EActionStage::PostAction:
		break;
	case EActionStage::PreDelay:
		GetWorld()->GetTimerManager().ClearTimer(PreDelayTimer);
		EndPostDelay();
		break;
	case EActionStage::PostDelay:
		GetWorld()->GetTimerManager().ClearTimer(PostDelayTimer);
		EndPostDelay();
		break;
	case EActionStage::Channel:
		GetWorld()->GetTimerManager().ClearTimer(ChannelTimer);
		EndChannel();
		break;
	default:
		break;
	}
	Stage = EActionStage::PostAction;
}
