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
	//��ü
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("UBoxComponent"));
	RootComponent = boxComp;

	//�ܰ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(boxComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABossHelixCPP::BeginPlay()
{
	Super::BeginPlay();

	// �귯���ð� * �ӷ� = �ӵ�
	theta += GetWorld()->RealTimeSeconds * 10;
}

// Called every frame
void ABossHelixCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//sine = ������(z), cosine ������(y)�ȿ� �ӵ��� �־���
	float s = FMath::Sin(theta);
	float c = FMath::Cos(theta);

	//������(150)�ʱⰪ�� �ð��� ������ Ŀ���� Delta�� 200�� ���� ���� �����ش�.
	helix += (DeltaTime * 300);

	//������ ��ġ���� �����ϱ� ���� ���忡�� ã�� boss������ �־��ش�
	for (TActorIterator<ABossEnemyCPP> it(GetWorld()); it; ++it)
	{
		boss = Cast<ABossEnemyCPP>(*it);
	}
	//������� ���ͺ����ȿ� *������ ��ġ���� �������� sine,cosine������ y,z�࿡ �־��ְ� 500�� ���� ���� �������� ���� �����ش�
	retVector = boss->GetActorLocation() + FVector(0, helix * c, helix * s);
	// ����(Bullet)�� ��ġ�� �ϼ��� ���ͺ���(���������� ����)�� �־��ش�
	SetActorLocation(retVector);
}

