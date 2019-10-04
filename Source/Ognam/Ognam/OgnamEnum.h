// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/*
**	Type of Ability. Affects key binding and UI
*/
UENUM()
enum class EAbilityType : uint8
{
	None,
	Mobility,
	Unique,
	Utility,
	Special,
};

/*
**	Abilities can have multiple status effects
**	Internally, it's a bit field(For now)
*/
UENUM()
enum class EStatusEffect : uint64
{
	None = 0x0, //No Status effect
	Rooted = 0x1, //Cannot give movement input
	Silenced = 0x2, //Cannot give ability input
	Unarmed = 0x4, //Cannot give weapon input
	Unbreakable = 0x8, //Cannot be damaged by outer damage (self damaging, dot damages are still applied), not implemented yet
};
ENUM_CLASS_FLAGS(EStatusEffect)

/*
**	Action Notifier Type is used for dispelling
*/
UENUM()
enum class EActionNotifier : uint64
{
	None,
	Jump,
	//Movement,
	SpecialMovement,
	Focus,	//General ability that requires focus. Can cancel reload
	Death
};

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
