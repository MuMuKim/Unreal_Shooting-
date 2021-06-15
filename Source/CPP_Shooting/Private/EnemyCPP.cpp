// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCPP.h"
#include <Components/BoxComponent.h> //�߰��ؾ���
#include <Components/StaticMeshComponent.h> //�߰��ؾ���
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
	//Box������Ʈ �߰��ϱ�
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollition"));
	//Box������Ʈ�� ��Ʈ������Ʈ�� ����
	RootComponent = boxComp;

	//StaticMesh������Ʈ �߰��ϱ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMesh������Ʈ�� ��Ʈ������Ʈ�� �ڽ����� ���
	meshComp->SetupAttachment(boxComp);
	//��Ʈ�� �浹ü�� �ֱ⋚���� �ڽ��� meshComp�� Collision�� ���ش�.
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//EnemyMove Component �߰�
	enemyMove = CreateDefaultSubobject<UEnemyMove>(TEXT("EnemyMove"));
	//EnemyMove Component �߰�
	enemyFire = CreateDefaultSubobject<UEnemyFire>(TEXT("EnemyFire"));

	//�Ѿ��� �ε��ؼ� �ٿ����� (Editor���� BP_EnemyBullet�� �����ؼ� �ٿ��ְ�, ���� _C�� �ٿ���� Ŭ������ �޾ƿ���)
	//BP���� Factory�� �Ҵ縻�� �ڵ忡�� �ε��� �Ҵ��ϴ¹��
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

