// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Killable.generated.h"

enum class EDamageMethod : uint64;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UKillable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OGNAM_API IKillable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:	//Fix signiture
	virtual bool CanBeKilledBy(class AOgnamPlayerState* DamageInstigator, EDamageMethod DamageMethod) = 0;
};


// 3 ways, nullptr as neutral / Keep FName as teams and then query the gamestate / Create Neutral PlayerState
//	-> AI playerstate	Problem is I dont know how to make a bot(even if it does nothing)
// checking if it deals damage to 

// parent class is OgnamEntity
// -> OE will inherit IDamagable (make abstract)
// breakable actor is child class