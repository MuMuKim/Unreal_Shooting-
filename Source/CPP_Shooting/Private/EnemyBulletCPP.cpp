// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBulletCPP.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
AEnemyBulletCPP::AEnemyBulletCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Box������Ʈ �߰��ϱ�
	spComp = CreateDefaultSubobject<USphereComponent>(TEXT("ShpereCollition"));
	//Box������Ʈ�� ��Ʈ������Ʈ�� ����
	RootComponent = spComp;

	//StaticMesh������Ʈ �߰��ϱ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMesh������Ʈ�� ��Ʈ������Ʈ�� �ڽ����� ���
	meshComp->SetupAttachment(spComp);
	//��Ʈ�� �浹ü�� �ֱ⋚���� �ڽ��� meshComp�� Collision�� ���ش�.
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

