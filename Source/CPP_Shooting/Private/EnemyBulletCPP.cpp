// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBulletCPP.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
AEnemyBulletCPP::AEnemyBulletCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Box컴포넌트 추가하기
	spComp = CreateDefaultSubobject<USphereComponent>(TEXT("ShpereCollition"));
	//Box컴포넌트를 루트컴포넌트로 설정
	RootComponent = spComp;

	//StaticMesh컴포넌트 추가하기
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMesh컴포넌트를 루트컴포넌트의 자식으로 등록
	meshComp->SetupAttachment(spComp);
	//루트의 충돌체가 있기떄문에 자식인 meshComp는 Collision을 꺼준다.
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AEnemyBulletCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBulletCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//P = P0 + vt
	SetActorLocation(GetActorLocation() + FVector(0, 0, -1) * 800 * DeltaTime);
}

