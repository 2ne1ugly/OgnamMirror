// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/*
**	Type of Ability. Affects key binding and UI
*/
UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	None,
	Mobility,
	Unique,
	Utility,
	Special,
	Max,
};

/*
**	Abilities can have multiple status effects
**	Internally, it's a bit field(For now)
*/
UENUM()
enum class EStatusEffect : uint64
{
	Rooted = 0x1, //Cannot give movement input
	Silenced = 0x2, //Cannot give ability input
	Unarmed = 0x3, //Cannot give weapon input
	Unbreakable = 0x4, //Cannot be damaged by outer damage (self damaging, dot damages are still applied), not implemented yet
};

/*
**	Action Notifier Type is used for dispelling
*/
UENUM()
enum class EActionNotifier : uint64
{
	None = 0x0,
	Jump = 0x1,
	SpecialMovement = 0x2,
	Focus = 0x4,	//General ability that requires focus. Can cancel reload
	Death = 0x8,
};
ENUM_CLASS_FLAGS(EActionNotifier)

/*
**	Action Stage is used in Action modifier
*/
UENUM()
enum class EActionStage : uint64
{
	PreAction,
	PreDelay,
	Channel,
	PostDelay,
	PostAction,
};

/*
**	Damage method describes which players should be affected by the damage
**	may have more entries on different gamemodes.
**	may have more entries when adding destructible walls or such?
*/
UENUM()
enum class EDamageMethod : uint64
{
	None = 0x0,
	DamagesSelf = 0x1,
	DamagesAlly = 0x2,	//Does not include yourself
	DamagesEnemy = 0x4,
};
ENUM_CLASS_FLAGS(EDamageMethod)
