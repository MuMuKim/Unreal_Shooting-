// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCPP.h"
#include <Components/BoxComponent.h> //추가해야함
#include <Components/StaticMeshComponent.h> //추가해야함
#include <Kismet/GameplayStatics.h>
#include "CPP_ShootingGameModeBase.h"
#include "PlayerCPP.h"


// Sets default values
AEnemyCPP::AEnemyCPP()
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
void AEnemyCPP::BeginPlay()
{
	Super::BeginPlay();

	//컴포넌트 충돌을 담당할 이벤트 함수를 연결하고 싶다.
	//필요한것 :처리할 이벤트 함수
	//->컴포넌트 충돌을 위해서는 AddDynamic함수를 이용해야한다
	//->AddDynamic 함수의 인자로 등록되는 함수는 반드시 UFUNCTION 매크로를 사용해야한다.
	//boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCPP::OnTriggerEnter);

	//TArray란 언리얼 배열.꺽세안에 담을 자료형을 넣어줌,주소를 받아야함(복사하지않기위해)
	TArray<AActor*> objs; // 타겟(플레이어)를 담을 그릇
	//동적할당 : 태어날 때 타겟을 찾아 넣자

	//월드상에 Actor을 찾아넣기 (배열로 담아야함)
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCPP::StaticClass(), objs);

	//for 문으로 objs검색
	for (AActor* actor : objs) //actor라는 임시변수에 objs의 담긴 자료만큼 돌아 넣는다
	{
		target = actor;
	}
	//위아래가 같은 것
	/*for (int i = 0; i < objs.Num(); i++)
	{
		target = objs[0];
	}*/

	//아래로 가되, 50%이하면 타겟방향으로 설정.
	//처음 dir값은 아래방향으로
	dir = FVector(0, 0, -1);

	//랜덤변수
	int32 ab = FMath::FRandRange(1, 100);
	
	//만약 타겟에 값이 제대로 들어 있다면 
	if (target != nullptr)
	{
		//랜덤 확률로 50%이하면 타겟방향
		if (ab <= 50)
		{
			//dir값에 타겟 - me 적용해 타겟방향을 구한다
			dir = target->GetActorLocation() - GetActorLocation();
		}
	}
}

// Called every frame
void AEnemyCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//방향구하기
	// 타겟이 있고, 타겟이 유효하다면(타겟이 죽었을 때 길잃은놈을 위해)
	if (target && IsValid(target))
	{
		dir; //태어날 때 방향 그대로
	}
	else
	{
		//아래로
		dir = FVector(0, 0, -1);
	}
	dir.Normalize();

	FVector v = dir * 500;

	FVector P0 = GetActorLocation();
	FVector P = P0 + v * DeltaTime;
	SetActorLocation(P,true);

}

//다른 물체와 겹쳤을 때 호출되는 이벤트 함수
//너죽고 나죽자
//void AEnemyCPP::NotifyActorBeginOverlap(AActor* OtherActor)


void AEnemyCPP::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Enemy 끼리 충돌하지 않게 하고 싶다.
	
	//OtherActor를 AEnemy로 형변환 한다. 안되면 NULL을 반환.
	AEnemyCPP* enemy = Cast<AEnemyCPP>(OtherActor);
	if (enemy != nullptr)
	{
		//만약에 enemy변수가 Null이 아니라면 아래를 실행하지 않는다
		return; //함수를 종료해준다
	}
	// 위아래 같은 결과
	/*if (OtherActor->GetName().Contains(TEXT("Enemy")))
	{
		return;
	}*/

	//폭발효과 생성
	//뒤부터 ->나의 Transform에서 ex를 인스턴스를 월드상에 시켜라
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory,
		GetActorTransform());
	//폭발효과 Sound
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	OtherActor->Destroy(); //너죽고
	Destroy(); //나죽자 this생략
}

void AEnemyCPP::OnCollisionEnter(AActor* OtherActor)
{
	//폭발효과 생성
	//뒤부터 ->나의 Transform에서 ex를 인스턴스를 월드상에 시켜라
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory,
		GetActorTransform());
	//폭발효과 Sound
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	//부딪힌 Actor가 Bullet일 경우 탄창에 다시 넣어주자
	//bullet 변수안에 otherActor(닿은액터)를 Bullet타입으로 형변환시킨다.
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	auto bullet = Cast<ABulletCPP>(OtherActor);
	if (bullet) //Bullet이 맞다면
	{
		//Bullet을 원래 자리로 넣어준다
		gameMode->AddBullet(bullet);
	}
	else
	{
		//부딪힌녀석이 Player면 
		auto player = Cast<APlayerCPP>(OtherActor);
		if (player)
		{
			//GameOver을 실행하고싶다
			gameMode->SetState(EGameState::GameOver);
		}
		OtherActor->Destroy(); //너죽고
	}

	//점수를 올려주자
	gameMode->SetCurrentScore(gameMode->GetCurrentScore() + 1);

	Destroy(); //나죽자 this생략
}

