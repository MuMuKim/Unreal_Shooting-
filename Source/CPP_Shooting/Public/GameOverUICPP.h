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
	//��ư�� �����ų �Լ�
	UFUNCTION()
	void OnRestartClickde();
	UFUNCTION()
	void OnQuitClickde();

	//UI Widjet ��������
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	class UButton* ReStart_Button;
	UPROPERTY(BluePrintReadWrite, meta=(BindWidget))
	class UButton* Quit_Button;

	// BP���� �ش� �Լ��� ȣ�� �� �� �ֵ���
	UFUNCTION(BlueprintCallable)
	void ReStart();
	UFUNCTION(BlueprintCallable)
	void Quit();
};
