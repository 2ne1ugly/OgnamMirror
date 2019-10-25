// Copyright 2019 Ognam Studios. All Rights Reserved.

#include "DamageText.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "ConstructorHelpers.h"

ADamageText::ADamageText()
{	
	InitialLifeSpan = 1.f;
	GetTextRender()->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	GetTextRender()->SetWorldSize(64.f);
	static ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant> Material(TEXT("MaterialInstanceConstant'/Game/Material/Text_Inst.Text_Inst'"));
	GetTextRender()->SetMaterial(0, Material.Object);
	//GetTextRender()->SetRenderInMainPass(false);
}

void ADamageText::SetDamage(float _Damage)
{
	Damage = _Damage;
	GetTextRender()->SetText(FString::Printf(TEXT("%.0f"), Damage));
}
