#pragma once

#include "CoreMinimal.h"
#include "Engine.h"

#if PLATFORM_WINDOWS
#define O_LOG_INTERNAL(Log, Level, Msg, ...) UE_LOG(Log, Level, TEXT("%s(%d): ") Msg, TEXT(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#else
#define O_LOG_INTERNAL(Log, Level, Msg, ...) UE_LOG(Log, Level, TEXT("%s(%d): ") Msg, *FString(__FUNCTION__), __LINE__, ##__VA_ARGS__)
#endif

#define O_LOG_E(Msg, ...) O_LOG_INTERNAL(LogTemp, Error, Msg, ##__VA_ARGS__)
#define O_LOG_F(Msg, ...) O_LOG_INTERNAL(LogTemp, Fatal, Msg, ##__VA_ARGS__)
#define O_LOG(Msg, ...) O_LOG_INTERNAL(LogTemp, Warning, Msg, ##__VA_ARGS__)
