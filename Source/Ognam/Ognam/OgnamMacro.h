#pragma once

#include "CoreMinimal.h"

#define O_LOG_INTERNAL(Log, Level, Msg, ...) UE_LOG(Log, Level, TEXT("%s(%d): ") Msg, TEXT(__FUNCTION__), __LINE__, __VA_ARGS__)
#define O_LOG_E(Msg, ...) O_LOG_INTERNAL(LogTemp, Error, Msg, __VA_ARGS__)
#define O_LOG_F(Msg, ...) O_LOG_INTERNAL(LogTemp, Fatal, Msg, __VA_ARGS__)
#define O_LOG(Msg, ...) O_LOG_INTERNAL(LogTemp, Warning, Msg, __VA_ARGS__)
