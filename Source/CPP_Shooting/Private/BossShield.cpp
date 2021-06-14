// Fill out your copyright notice in the Description page of Project Settings.


#include "BossShield.h"
#include "CPP_ShootingGameModeBase.h"
#include <Components/ArrowComponent.h>
#include "BossBulletCPP.h"
#include <EngineUtils.h>
#include "BossEnemyCPP.h"


// Sets default values for this component's properties
UBossShield::UBossShield()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBossShield::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<ABossEnemyCPP>(GetOwner());
	// 흘러간시간 * 속력 = 속도
	theta += GetWorld()->RealTimeSeconds * 5;
}


// Called every frame
void UBossShield::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	//Playing모드가 아닐시 리턴
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	//현재시간
	currentTime += DeltaTime;
	//현재시간이 경과시간을 초과하면
	if (currentTime / 2 && currentTime > 5)
	{
		if (bulletFactory)
		{
			//생성될때 오브젝트가 겹쳐도 가능하게
			FActorSpawnParameters pram;
			pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			//총구위치에서 총알공장에서 만들어진 총알을 발사
			auto bullet = GetWorld()->SpawnActor<ABossBulletCPP>(bulletFactory, me->firePosition->GetComponentLocation(), me->firePosition->GetComponentRotation(), pram);
			
			//sine = 세로축(z), cosine 가로축(y)안에 속도를 넣어줌
			float s = FMath::Sin(theta);
			float c = FMath::Cos(theta);

			//반지름(150)초기값에 시간이 갈수록 커지게 Delta에 200을 곱한 수를 더해준다.
			//helix += (DeltaTime * 200);

			//만들어준 백터변수안에 *보스의 위치에서 만들어놓은 sine,cosine변수를 y,z축에 넣어주고 500를 곱해 원의 반지름을 정해 더해준다
			retVector = me->GetActorLocation() + FVector(0, 500*c, 500*s);
			// 나의(Bullet)의 위치를 완성한 백터변수(보스주위를 도는)를 넣어준다
			bullet->SetActorLocation(retVector);
			//현재시간 초기화
			if (currentTime > 9)
			{
				currentTime = 0;
				for (TActorIterator<ABossBulletCPP> it(GetWorld()); it; ++it)
				{
					it->Destroy();
				}
			}
		}
	}
}

