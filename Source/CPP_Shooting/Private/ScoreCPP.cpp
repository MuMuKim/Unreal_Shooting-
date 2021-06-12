// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreCPP.h"
#include <Components/TextBlock.h>

void UScoreCPP::PrintCurrentScore(int32 point)
{
	// ���� Current Score UI�� �ִٸ� 
	if (Text_CurrentScore)
	{
		// UTextBlock <- Inculude ������Ѵ�
		//-> Point�� �Ҵ��������
		FString scoreStr = FString::Printf(TEXT("Current Score: %d"), point);
		//UI�� ���� �Ҵ�
		Text_CurrentScore->SetText(FText::FromString(scoreStr));
	}
}

void UScoreCPP::PrintTopScore(int32 point)
{
	// ���� Current Score UI�� �ִٸ� 
	if (Text_TopScore)
	{
		// UTextBlock <- Inculude ������Ѵ�
		//-> Point�� �Ҵ��������
		FString scoreStr = FString::Printf(TEXT("Top Score: %d"), point);
		//UI�� ���� �Ҵ�
		Text_TopScore->SetText(FText::FromString(scoreStr));
	}
}
