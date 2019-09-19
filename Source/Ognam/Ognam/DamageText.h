// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TextRenderActor.h"
#include "DamageText.generated.h"

/**
 * 
 */
UCLASS()
class OGNAM_API ADamageText : public ATextRenderActor
{
	GENERATED_BODY()

public:
	ADamageText();

	void SetDamage(float _Damage);

protected:
	float Damage;
};
