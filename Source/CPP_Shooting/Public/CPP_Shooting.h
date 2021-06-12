// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Shooting, Log, All)

//��𿡼� �α׸� ��� �ִ���, �ٹ�ȣ���� �˷��ִ� ���
//CALLINFO�� �Լ��� �˷���
#define CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define PRINT_CALLINFO() UE_LOG(Shooting, Warning, TEXT("%s"), *CALLINFO)
// ...�� ��������(�������� ���ڰ� ���ü��ִٴ¶�
#define PRINTLOG(fmt, ...) UE_LOG(Shooting, Warning, TEXT("%s %s"), *CALLINFO, *FString::Printf(fmt,##__VA_ARGS__))

