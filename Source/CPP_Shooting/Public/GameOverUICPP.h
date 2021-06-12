// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverUICPP.generated.h"

/**
 * 
 */
UCLASS()
class CPP_SHOOTING_API UGameOverUICPP : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	//버튼을 실행시킬 함수
	UFUNCTION()
	void OnRestartClickde();
	UFUNCTION()
	void OnQuitClickde();

	//UI Widjet 가져오기
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UButton* ReStart_Button;
	UPROPERTY(BluePrintReadWrite, meta=(BindWidget))
	class UButton* Quit_Button;

	// BP에서 해당 함수를 호출 할 수 있도록
	UFUNCTION(BlueprintCallable)
	void ReStart();
	UFUNCTION(BlueprintCallable)
	void Quit();
};
