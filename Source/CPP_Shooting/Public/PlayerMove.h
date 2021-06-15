// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/InputComponent.h>
#include "PlayerMove.generated.h"

// meta = �������Ʈ�ȿ� AddComponent�Ҷ� ã�� �� ����
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_SHOOTING_API UPlayerMove : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//����� �Է�ó�� ����� �Լ� (�ݹ�: Callback)
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	//�¿� �Է°� ó�� �Լ� ����
	void InputHorizontal(float value);

	//�¿� �Է°� ó�� �Լ� ����
	void InputVertical(float value);

	//�¿� �Է��� �޾��� �� �ش� �������� �̵��ϰ� �ʹ�
	UPROPERTY()
	float h = 0;
	UPROPERTY()
	float vertical = 0;

	UPROPERTY(EditAnywhere, Category="Speed")
	float spped = 1000;

	//�� ������Ʈ�� �����ϰ� �ִ� ���� ��ü
	UPROPERTY()
	class APlayerCPP* me;
};
