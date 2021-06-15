// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/InputComponent.h>
#include "PlayerMove.generated.h"

// meta = 블루프린트안에 AddComponent할때 찾을 수 있음
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

	//사용자 입력처리 담당할 함수 (콜백: Callback)
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	//좌우 입력값 처리 함수 선언
	void InputHorizontal(float value);

	//좌우 입력값 처리 함수 선언
	void InputVertical(float value);

	//좌우 입력을 받았을 때 해당 방향으로 이동하고 싶다
	UPROPERTY()
	float h = 0;
	UPROPERTY()
	float vertical = 0;

	UPROPERTY(EditAnywhere, Category="Speed")
	float spped = 1000;

	//이 컴포넌트를 소유하고 있는 액터 객체
	UPROPERTY()
	class APlayerCPP* me;
};
