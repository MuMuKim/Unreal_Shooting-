// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Shooting, Log, All)

//어디에서 로그를 찍고 있는지, 줄번호까지 알려주는 기능
//CALLINFO는 함수를 알려줌
#define CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define PRINT_CALLINFO() UE_LOG(Shooting, Warning, TEXT("%s"), *CALLINFO)
// ...은 가변인자(여러개의 인자가 들어올수있다는뜻
#define PRINTLOG(fmt, ...) UE_LOG(Shooting, Warning, TEXT("%s %s"), *CALLINFO, *FString::Printf(fmt,##__VA_ARGS__))

