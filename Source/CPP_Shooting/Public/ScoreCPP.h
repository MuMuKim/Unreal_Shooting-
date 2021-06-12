// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreCPP.generated.h"

/**
 * 
 */
UCLASS()
class CPP_SHOOTING_API UScoreCPP : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	class UTextBlock* Text_CurrentScore;

	UPROPERTY(BlueprintReadWrite,meta = (BindWidget))
	class UTextBlock* Text_TopScore;

	// Current Score ����ϴ� �Լ�
	void PrintCurrentScore(int32 point);

	// Top Score ����ϴ� �Լ�
	void PrintTopScore(int32 point);
};
