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

	//��ü
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = boxComp;

	//�ܰ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABossBulletCPP::BeginPlay()
{
	Super::BeginPlay();
	
	//���忡�� player�� ã��
	for (TActorIterator<APlayerCPP> it(GetWorld()); it; ++it)
	{
		// Ÿ�ٺ����ȿ� Player�� �ִ´�
		target = *it;
	}
	// Ÿ��(Player)���ⱸ�ϱ�
	dir = target->GetActorLocation() - GetActorLocation();
	// ���� ����ȭ
	dir.Normalize();
	
	
	//�������� �������ϱ�
	/*dir = FVector(0, 0, -1);
	int32 ran = FMath::RandRange(1, 2);
	if (target != nullptr)
	{
		if (ran == 2)
		{
			
		}
	}*/
	
	// �귯���ð� * �ӷ� = �ӵ�
	theta += GetWorld()->RealTimeSeconds * 5;
}

// 1.�����ð��� �Ǹ� Player�������� Bullet�� �������� 5���� ���ʹ�
// ->�Ѿ��� �߻��ؾ��Ѵ�
// ->player������ ã�´�
// ->�����ð��� ������

// 2.���� �������� ������ ������ �������¸� �̷�� Bullet�� ����� �ʹ�
// ->���� ������ �߻��Ѵ�
// ->������ ���� ���ÿ� ������ ���۵���
// ->�����ð��� �Ǹ�
void ABossBulletCPP::Tick(float DeltaTime)
{
	
	
	//�̵� P = P0 + vt
	SetActorLocation(GetActorLocation() + dir * speed * DeltaTime, true);

	FRotator r =  FRotator(0, 1, 0);
	SetActorRotation(GetActorRotation() + r * speed * DeltaTime);
}


