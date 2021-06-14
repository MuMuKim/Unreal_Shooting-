// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBulletCPP.h"
#include <Components/StaticMeshComponent.h>
#include <Components/SphereComponent.h>
#include <Components/BoxComponent.h>
#include "PlayerCPP.h"
#include <EngineUtils.h>
#include "BossEnemyCPP.h"
#include <Math/UnrealMathUtility.h>

ABossBulletCPP::ABossBulletCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//몸체
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = boxComp;

	//외관
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABossBulletCPP::BeginPlay()
{
	Super::BeginPlay();
	
	//월드에서 player를 찾아
	for (TActorIterator<APlayerCPP> it(GetWorld()); it; ++it)
	{
		// 타겟변수안에 Player를 넣는다
		target = *it;
	}
	// 타겟(Player)방향구하기
	dir = target->GetActorLocation() - GetActorLocation();
	// 방향 정규화
	dir.Normalize();
	
	
	//랜덤으로 방향정하기
	/*dir = FVector(0, 0, -1);
	int32 ran = FMath::RandRange(1, 2);
	if (target != nullptr)
	{
		if (ran == 2)
		{
			
		}
	}*/
	
	// 흘러간시간 * 속력 = 속도
	theta += GetWorld()->RealTimeSeconds * 5;
}

// 1.일정시간이 되면 Player방향으로 Bullet을 연속으로 5발을 쏘고싶다
// ->총알을 발사해야한다
// ->player방향을 찾는다
// ->일정시간이 지나면

// 2.나를 기점으로 앞으로 나가며 나선형태를 이루는 Bullet을 만들고 싶다
// ->총을 앞으로 발사한다
// ->앞으로 가는 동시에 주위를 빙글돈다
// ->일정시간이 되면
void ABossBulletCPP::Tick(float DeltaTime)
{
	
	
	//이동 P = P0 + vt
	SetActorLocation(GetActorLocation() + dir * speed * DeltaTime, true);

	FRotator r =  FRotator(0, 1, 0);
	SetActorRotation(GetActorRotation() + r * speed * DeltaTime);
}


