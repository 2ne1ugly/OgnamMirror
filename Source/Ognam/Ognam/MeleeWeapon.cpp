// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Ognam/OgnamCharacter.h"
#include "Components/PrimitiveComponent.h"
#include "UnrealNetwork.h"

UMeleeWeapon::UMeleeWeapon()
{
	PreSwing = .25f;
	PeriSwing = .7f;
	PostSwing = .15f;
}

void UMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (!TriggerClass)
	{
		UE_LOG(LogTemp, Error, TEXT("No Trigger Zone"));
		return;
	}
	Trigger = NewObject<UPrimitiveComponent>(Target, TriggerClass, TEXT("WeaponTrigger"));

	Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Trigger->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Trigger->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &UMeleeWeapon::BeginOverlap);
	Trigger->MoveIgnoreActors.Add(Target);

	Trigger->RegisterComponent();
}

void UMeleeWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMeleeWeapon, bSwinging);
	DOREPLIFETIME_CONDITION(UMeleeWeapon, bWantsToSwing, COND_OwnerOnly);
}

void UMeleeWeapon::BasicPressed()
{
	if (Target->HasStatusEffect(EStatusEffect::Unarmed))
	{
		return;
	}
	ServerBasicPressed();
}

void UMeleeWeapon::ServerBasicPressed_Implementation()
{
	if (Target->HasStatusEffect(EStatusEffect::Unarmed))
	{
		return;
	}
	bWantsToSwing = true;
	if (!bSwinging)
	{
		bSwinging = true;
		StartPreSwing();
	}
}

void UMeleeWeapon::BasicReleased()
{
	ServerBasicReleased();
}

void UMeleeWeapon::ServerBasicReleased_Implementation()
{
	bWantsToSwing = false;
}

void UMeleeWeapon::StartPreSwing()
{
	GetWorld()->GetTimerManager().SetTimer(PreSwingTimer, this, &UMeleeWeapon::StartPeriSwing, PreSwing, false);
}

void UMeleeWeapon::StartPeriSwing()
{
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StrikedCharacters.Reset();
	GetWorld()->GetTimerManager().SetTimer(PeriSwingTimer, this, &UMeleeWeapon::StartPostSwing, PeriSwing, false);
}

void UMeleeWeapon::StartPostSwing()
{
	Trigger->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetWorld()->GetTimerManager().SetTimer(PostSwingTimer, this, &UMeleeWeapon::EndPostSwing, PostSwing, false);
}

void UMeleeWeapon::EndPostSwing()
{
	if (bWantsToSwing)
	{
		StartPreSwing();
	}
	else
	{
		bSwinging = false;
	}
}

void UMeleeWeapon::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOgnamCharacter* Character = Cast<AOgnamCharacter>(OtherActor);
	if (Character && !StrikedCharacters.Contains(Character))
	{
		StrikedCharacters.Add(Character);
		CharacterStrike(Character);
	}
}

void UMeleeWeapon::CharacterStrike(AOgnamCharacter* OtherCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Character Striked!"));
}

void UMeleeWeapon::StatusEffectApplied(EStatusEffect StatusEffect)
{
	if ((StatusEffect & EStatusEffect::Unarmed) != EStatusEffect::None &&
		Target->HasAuthority())
	{
		bWantsToSwing = false;
	}
}

void UMeleeWeapon::ActionTaken(EActionNotifier ActionType)
{
}

