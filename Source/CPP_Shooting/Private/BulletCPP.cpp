// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletCPP.h"
#include <Components/BoxComponent.h> //추가해야함
#include <Components/StaticMeshComponent.h> //추가해야함

// Sets default values
ABulletCPP::ABulletCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Box컴포넌트 추가하기
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollition"));
	//Box컴포넌트를 루트컴포넌트로 설정
	RootComponent = boxComp;

	//StaticMesh컴포넌트 추가하기
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMesh컴포넌트를 루트컴포넌트의 자식으로 등록
	meshComp->SetupAttachment(boxComp);
	//루트의 충돌체가 있기떄문에 자식인 meshComp는 Collision을 꺼준다.
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABulletCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector v = FVector(0, 0, 1);//방향
	v.Normalize(); //정규화
	v *= 1000; //v에 500을 곱함(속도)
	FVector P0 = GetActorLocation(); //현재위치를 가져옴
	FVector P = P0 + v * DeltaTime; // P = P0 + vt
	SetActorLocation(P,true);// 위치지정 -> 위치이동

}

