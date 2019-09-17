// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Modifier.generated.h"

/*
**	Abilities can have multiple status effects
**	Internally, it's a bit field(For now)
*/
UENUM()
enum class EStatusEffect : uint64
{
	None =			0x0, //No Status effect
	Rooted =		0x1, //Cannot give movement input
	Silenced =		0x2, //Cannot give ability input
	Unarmed =		0x4, //Cannot give weapon input
	Unbreakable =	0x8, //Cannot be damaged by outer damage (self damaging, dot damages are still applied), not implemented yet
};
ENUM_CLASS_FLAGS(EStatusEffect)

/**
 *	Modifier can be applied to Characters.
 *	If Someone wants to expand this to specific Interface than characters, more than welcomed.
 *	But for now, it's only intended for AOgnamCharacters.
 *	Access Target to get information to attached character.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OGNAM_API UModifier : public UActorComponent
{
	GENERATED_BODY()

public:
	UModifier();

	virtual bool ShouldEnd();
	virtual void TickModifier(float DeltaTime);
	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	EStatusEffect GetStatusEffect() const;

protected:
	virtual void BeginModifier();
	virtual void EndModifier();
	/*
	**	Props
	*/
	//UPROPERTY(VisibleAnywhere)
	//Sprite propery to show through modifier list.

	UPROPERTY(VisibleAnywhere)
	class AOgnamCharacter* Target;

	EStatusEffect StatusEffect;
};
