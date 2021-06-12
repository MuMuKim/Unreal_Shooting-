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

	// GameMode의 State가 Playing이 아니라면 아래 코드는 실행되지 않도록 하고 싶다.
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}



	//----------------------------------
	//P=P0+vt
	//RightFVector -> (x,y,z) (0,1,0) 
	//FVector v = FVector::RightVector; 으로도 쓸수있음
	FVector v = FVector(0, h, vertical);//방향
	v.Normalize(); //정규화
	v *= spped; //v에 500을 곱함(속도)
	FVector P0 = me->GetActorLocation(); //현재위치를 가져옴
	FVector P = P0 + v * DeltaTime; // P = P0 + vt
	me->SetActorLocation(P, true);// 위치지정 -> 위치이동

	//----------------------------------
	//Player을 제자리에서 Yal축으로 돌게 만들고싶다
	//R = R0 + rt
	FRotator r = FRotator(0, 1, 0) * 500; //방향 * 속도
	FRotator R0 = me->GetActorRotation(); //현재 방향
	FRotator R = R0 + r * DeltaTime; // R = R0 + rt
	me->SetActorRotation(R); // 방향회전
}

void UPlayerMove::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//좌우
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &UPlayerMove::InputHorizontal);
	//상하
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &UPlayerMove::InputVertical);
}

// 사용자의 Horizontal 입력을 처리할 함수
void UPlayerMove::InputHorizontal(float value)
{
	h = value; //멤버
}

void UPlayerMove::InputVertical(float value)
{
	vertical = value;
}
