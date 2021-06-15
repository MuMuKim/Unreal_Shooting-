// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBulletCPP.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include "CPP_ShootingGameModeBase.h"
#include "BulletCPP.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerCPP.h"

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

void AEnemyBulletCPP::OnCollisionEnter(AActor* OtherActor)
{
	//폭발효과 생성
	//뒤부터 ->나의 Transform에서 ex를 인스턴스를 월드상에 시켜라
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory,GetActorTransform());
	//폭발효과 Sound
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	//부딪힌녀석이 Player면 
	auto player = Cast<APlayerCPP>(OtherActor);
	if (player) //Bullet이 맞다면
	{
		//GameOver을 실행하고싶다
		auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
		gameMode->SetState(EGameState::GameOver);
	}
	
	OtherActor->Destroy(); //너죽고
	Destroy(); //나죽자 this생략
}
