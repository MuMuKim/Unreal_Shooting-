// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "CPP_Shooting.h" //매크로 함수를 만들 때 위의 Core은 이미 포함하기 때문에 지워줌
#include "BulletCPP.h"
#include "GameFramework/Pawn.h"
#include "PlayerFire.h"
#include "PlayerCPP.generated.h"

//BoxCollider 컴포넌트를 추가하고 싶다.
UCLASS()
class CPP_SHOOTING_API APlayerCPP : public APawn
{
	GENERATED_BODY()

public:
	//접근권한 DefaultsOnly는 BluePrint를 뜻하고, InstanceOnly는 Instance를 뜻함,
	//Visible은 보이기는 하되, 수정은 불가.
	//UPROPERTY(EditAnywhere,EditDefaultsOnly,EditInstanceOnly,VisibleAnywhere,VisibleDefaultsOnly,VisibleDefaultsOnly)

	UPROPERTY(EditAnywhere, Category="Component") //Editor에서 수정가능하게 해줌
 	class UBoxComponent* boxComp; //Box컴포넌트 추가

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;
	//총구위치
	UPROPERTY(EditAnywhere, Category = "Component")
	class UArrowComponent* firePosition;

	//PlayerMove 컴포넌트 추가
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UPlayerMove* playerMove;

	//PlayerFire 컴포넌트 추가
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UPlayerFire* playerFire;

	//공장
	//UPROPERTY(EditDefaultsOnly, Category = "BulletClass")
	//TSubclassOf<class ABulletCPP> bulletFactory;
	//총알 발사 처리 함수
	void Fire();
	//총알 발사 Sound
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* bulletSound;
public:
	// Sets default values for this pawn's properties
	APlayerCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//좌우 입력값 처리 함수 선언
	void InputHorizontal(float value);

};
