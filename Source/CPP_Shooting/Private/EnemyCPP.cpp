// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCPP.h"
#include <Components/BoxComponent.h> //추가해야함
#include <Components/StaticMeshComponent.h> //추가해야함
#include <Kismet/GameplayStatics.h>
#include "CPP_ShootingGameModeBase.h"
#include "PlayerCPP.h"
#include "EnemyMove.h"
#include "EnemyFire.h"
#include "EnemyBulletCPP.h"


// Sets default values
AEnemyCPP::AEnemyCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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

	//EnemyMove Component 추가
	enemyMove = CreateDefaultSubobject<UEnemyMove>(TEXT("EnemyMove"));
	//EnemyMove Component 추가
	enemyFire = CreateDefaultSubobject<UEnemyFire>(TEXT("EnemyFire"));

	//총알을 로드해서 붙여주자 (Editor에서 BP_EnemyBullet을 복사해서 붙여주고, 끝에 _C를 붙여줘야 클래스로 받아와짐)
	//BP에서 Factory에 할당말고 코드에서 로드해 할당하는방법
	ConstructorHelpers::FClassFinder<AEnemyBulletCPP> tempBullet(TEXT("Blueprint'/Game/BluePrint/BP_EnemyBullet.BP_EnemyBullet_c'"));
	if (tempBullet.Succeeded())
	{
		enemyFire->bulletFactory = tempBullet.Class;
	}
}

// Called when the game starts or when spawned
void AEnemyCPP::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

