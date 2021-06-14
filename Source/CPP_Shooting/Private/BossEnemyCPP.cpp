// Fill out your copyright notice in the Description page of Project Settings.


#include "BossEnemyCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include "BossBulletCPP.h"
#include <Engine/EngineTypes.h>
#include "CPP_ShootingGameModeBase.h"
#include "BulletCPP.h"
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>
#include "BossShield.h"
#include "BossShieldCPP.h"
#include "BossHelixCPP.h"


ABossEnemyCPP::ABossEnemyCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//몸체
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	//boxComp를 루트컴포넌트로
	RootComponent = boxComp;
	//외관
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//루트의 자식으로
	meshComp->SetupAttachment(boxComp);
	//외관의 충돌체 끄기
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//총구
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	//루트의 자식으로
	firePosition->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ABossEnemyCPP::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentHit.AddDynamic(this, &ABossEnemyCPP::OnColliderEnter);
}

// 1 게임이 시작되면 2초간 방어막 생성
// 2 방어막이 지워진 후 3초간 레이저 발사
// 3 레이저 발사 후 2초 뒤 3초간 나선공격 
void ABossEnemyCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	//Playing모드가 아닐시 리턴
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}
	//현재시간
	currentTime += DeltaTime;
	//현재시간이 경과시간을 초과하면
	if (currentTime / 2)
	{
		//방어막
		if (shieldFactory)
		{
			//생성될때 오브젝트가 겹쳐도 가능하게
			FActorSpawnParameters pram;
			pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			//총구위치에서 총알공장에서 만들어진 총알을 발사
			GetWorld()->SpawnActor<ABossShieldCPP>(shieldFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation(), pram);
			//현재시간 초기화
			if (currentTime > 2)
			{
				for (TActorIterator<ABossShieldCPP> it(GetWorld()); it; ++it)
				{
					it->Destroy();
				}
			}
		}
		//레이저발사
		if (bulletFactory && currentTime >= 3)
		{
			//생성될때 오브젝트가 겹쳐도 가능하게
			FActorSpawnParameters pram;
			pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			//총구위치에서 총알공장에서 만들어진 총알을 발사
			GetWorld()->SpawnActor<ABossBulletCPP>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation(), pram);
			//현재시간 초기화
			if (currentTime > 6)
			{
				for (TActorIterator<ABossBulletCPP> it(GetWorld()); it; ++it)
				{
					it->Destroy();
				}
			}
		}
		//나선공격 발사
		if (helixFactory && currentTime >= 8)
		{
			//생성될때 오브젝트가 겹쳐도 가능하게
			FActorSpawnParameters pram;
			pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			//총구위치에서 총알공장에서 만들어진 총알을 발사
			GetWorld()->SpawnActor<ABossHelixCPP>(helixFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation(), pram);
			//현재시간 초기화
			if (currentTime > 11)
			{
				for (TActorIterator<ABossHelixCPP> it(GetWorld()); it; ++it)
				{
					it->Destroy();
					if (currentTime > 13)
					{
						currentTime = 0;
					}
				}
			}
		}
	}

	//test 이동
	//SetActorLocation(GetActorLocation() + FVector(0, 0, -1) * 100 * DeltaTime);
}

void ABossEnemyCPP::OnColliderEnter(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//bullet을 변수로 받아온다
	auto bullet = Cast<ABulletCPP>(OtherActor);
	//GameMode를 받아온다
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	//방어코드
	if (bullet == nullptr)
	{
		return;
	}
	//부딪힌 Actor가 Bullet이라면
	if (OtherActor == bullet)
	{
		//맞은 횟수를 1올리고
		point +=1;
		//불렛을 탄창에 넣어준다
		gameMode->AddBullet(bullet);
		//20발이상 맞는다면
		if (point == 20)
		{
			//폭발효과,폭발사운드
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), expolsionFactory, GetActorLocation());
			UGameplayStatics::SpawnSound2D(GetWorld(), expolsionSound);
			//죽는다
			Destroy();
			//맞은 횟수 초기화
			point = 0;
		}
	}
}

