// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "CPP_Shooting.h" //��ũ�� �Լ��� ���� �� ���� Core�� �̹� �����ϱ� ������ ������
#include "BulletCPP.h"
#include "GameFramework/Pawn.h"
#include "PlayerFire.h"
#include "PlayerCPP.generated.h"

//BoxCollider ������Ʈ�� �߰��ϰ� �ʹ�.
UCLASS()
class CPP_SHOOTING_API APlayerCPP : public APawn
{
	GENERATED_BODY()

public:
	//���ٱ��� DefaultsOnly�� BluePrint�� ���ϰ�, InstanceOnly�� Instance�� ����,
	//Visible�� ���̱�� �ϵ�, ������ �Ұ�.
	//UPROPERTY(EditAnywhere,EditDefaultsOnly,EditInstanceOnly,VisibleAnywhere,VisibleDefaultsOnly,VisibleDefaultsOnly)

	UPROPERTY(EditAnywhere, Category="Component") //Editor���� ���������ϰ� ����
 	class UBoxComponent* boxComp; //Box������Ʈ �߰�

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;
	//�ѱ���ġ
	UPROPERTY(EditAnywhere, Category = "Component")
	class UArrowComponent* firePosition;

	//PlayerMove ������Ʈ �߰�
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UPlayerMove* playerMove;

	//PlayerFire ������Ʈ �߰�
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UPlayerFire* playerFire;

	//����
	//UPROPERTY(EditDefaultsOnly, Category = "BulletClass")
	//TSubclassOf<class ABulletCPP> bulletFactory;
	//�Ѿ� �߻� ó�� �Լ�
	void Fire();
	//�Ѿ� �߻� Sound
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

	//�¿� �Է°� ó�� �Լ� ����
	void InputHorizontal(float value);

};
