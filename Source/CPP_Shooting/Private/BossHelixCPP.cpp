// Fill out your copyright notice in the Description page of Project Settings.


#include "BossHelixCPP.h"
#include <Components/StaticMeshComponent.h>
#include "BossEnemyCPP.h"
#include <EngineUtils.h>
#include <Components/BoxComponent.h>

// Sets default values
ABossHelixCPP::ABossHelixCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//몸체
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("UBoxComponent"));
	RootComponent = boxComp;

	//외관
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABossHelixCPP::BeginPlay()
{
	Super::BeginPlay();

	// 흘러간시간 * 속력 = 속도
	theta += GetWorld()->RealTimeSeconds * 10;
}

// Called every frame
void ABossHelixCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//sine = 세로축(z), cosine 가로축(y)안에 속도를 넣어줌
	float s = FMath::Sin(theta);
	float c = FMath::Cos(theta);

	//반지름(150)초기값에 시간이 갈수록 커지게 Delta에 200을 곱한 수를 더해준다.
	helix += (DeltaTime * 300);

	//보스의 위치값을 대입하기 위해 월드에서 찾아 boss변수에 넣어준다
	for (TActorIterator<ABossEnemyCPP> it(GetWorld()); it; ++it)
	{
		boss = Cast<ABossEnemyCPP>(*it);
	}
	//만들어준 백터변수안에 *보스의 위치에서 만들어놓은 sine,cosine변수를 y,z축에 넣어주고 500를 곱해 원의 반지름을 정해 더해준다
	retVector = boss->GetActorLocation() + FVector(0, helix * c, helix * s);
	// 나의(Bullet)의 위치를 완성한 백터변수(보스주위를 도는)를 넣어준다
	SetActorLocation(retVector);
}

