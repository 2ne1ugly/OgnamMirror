// Fill out your copyright notice in the Description page of Project Settings.


#include "HereiraExplosiveArrowReady.h"

bool UHereiraExplosiveArrowReady::ShouldEnd()
{
	return bUsed;
}

bool UHereiraExplosiveArrowReady::Use()
{
	bool bResult = !bUsed;
	bUsed = true;
	return bResult;
}
