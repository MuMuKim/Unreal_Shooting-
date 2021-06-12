// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreCPP.h"
#include <Components/TextBlock.h>

void UScoreCPP::PrintCurrentScore(int32 point)
{
	// 만약 Current Score UI가 있다면 
	if (Text_CurrentScore)
	{
		// UTextBlock <- Inculude 해줘야한다
		//-> Point를 할당시켜주자
		FString scoreStr = FString::Printf(TEXT("Current Score: %d"), point);
		//UI에 값을 할당
		Text_CurrentScore->SetText(FText::FromString(scoreStr));
	}
}

void UScoreCPP::PrintTopScore(int32 point)
{
	// 만약 Current Score UI가 있다면 
	if (Text_TopScore)
	{
		// UTextBlock <- Inculude 해줘야한다
		//-> Point를 할당시켜주자
		FString scoreStr = FString::Printf(TEXT("Top Score: %d"), point);
		//UI에 값을 할당
		Text_TopScore->SetText(FText::FromString(scoreStr));
	}
}
