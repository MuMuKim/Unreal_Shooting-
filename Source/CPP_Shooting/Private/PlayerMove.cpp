// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMove.h"
#include "CPP_ShootingGameModeBase.h"
#include "PlayerCPP.h"

// Sets default values for this component's properties
UPlayerMove::UPlayerMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerMove::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<APlayerCPP>(GetOwner());
}


// Called every frame
void UPlayerMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// GameMode�� State�� Playing�� �ƴ϶�� �Ʒ� �ڵ�� ������� �ʵ��� �ϰ� �ʹ�.
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}



	//----------------------------------
	//P=P0+vt
	//RightFVector -> (x,y,z) (0,1,0) 
	//FVector v = FVector::RightVector; ���ε� ��������
	FVector v = FVector(0, h, vertical);//����
	v.Normalize(); //����ȭ
	v *= spped; //v�� 500�� ����(�ӵ�)
	FVector P0 = me->GetActorLocation(); //������ġ�� ������
	FVector P = P0 + v * DeltaTime; // P = P0 + vt
	me->SetActorLocation(P, true);// ��ġ���� -> ��ġ�̵�

	//----------------------------------
	//Player�� ���ڸ����� Yal������ ���� �����ʹ�
	//R = R0 + rt
	FRotator r = FRotator(0, 1, 0) * 500; //���� * �ӵ�
	FRotator R0 = me->GetActorRotation(); //���� ����
	FRotator R = R0 + r * DeltaTime; // R = R0 + rt
	me->SetActorRotation(R); // ����ȸ��
}

void UPlayerMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//�¿�
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &UPlayerMove::InputHorizontal);
	//����
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &UPlayerMove::InputVertical);
}

// ������� Horizontal �Է��� ó���� �Լ�
void UPlayerMove::InputHorizontal(float value)
{
	h = value; //���
}

void UPlayerMove::InputVertical(float value)
{
	vertical = value;
}
