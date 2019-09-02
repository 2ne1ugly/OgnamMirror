// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Modifier.generated.h"

/**
 *	Modifier can be applied to Characters.
 *	If Someone wants to expand this to specific Interface than characters, more than welcomed.
 *	But for now, it's only intended for AOgnamCharacters.
 *	Access Target to get information to attached character.
 */
UCLASS()
class OGNAM_API UModifier : public UObject
{
	GENERATED_BODY()

public:
	/*
	**	Exported Functions
	*/
	void GetApplied(class AOgnamCharacter* Character);
	void GetDetached();
	bool IsActive() const;
	virtual bool ShouldEnd();
	virtual void TickModifier(float DeltaTime);

protected:
	/*
	**	Inherited Functions
	*/
	//Executed when begining of modifier. Usually applied for Visual Effects with this.
	virtual void BeginModifier();
	virtual void EndModifier();

	/*
	**	Props
	*/
	//UPROPERTY(VisibleAnywhere)
	//Sprite propery to show through modifier list.

	UPROPERTY(VisibleAnywhere)
	bool bActive;

	UPROPERTY(VisibleAnywhere)
	class AOgnamCharacter* Target;	
};
