// Fill out your copyright notice in the Description page of Project Settings.


#include "BossShieldCPP.h"
#include <Components/SphereComponent.h>
#include "BossEnemyCPP.h"
#include <EngineUtils.h>

// Sets default values
ABossShieldCPP::ABossShieldCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//��ü
	spComp = CreateDefaultSubobject<USphereComponent>(TEXT("USphereComponent"));
	RootComponent = spComp;

	//�ܰ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	meshComp->SetupAttachment(spComp);
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ABossShieldCPP::BeginPlay()
{
	Super::BeginPlay();

	// �귯���ð� * �ӷ� = �ӵ�
	theta += GetWorld()->RealTimeSeconds * 5;
}

// Called every frame
void ABossShieldCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//sine = ������(z), cosine ������(y)�ȿ� �ӵ��� �־���
	float s = FMath::Sin(theta);
	float c = FMath::Cos(theta);

	//������ ��ġ���� �����ϱ� ���� ���忡�� ã�� boss������ �־��ش�
	for (TActorIterator<ABossEnemyCPP> it(GetWorld()); it; ++it)
	{
		boss = Cast<ABossEnemyCPP>(*it);
	}
	//������� ���ͺ����ȿ� *������ ��ġ���� �������� sine,cosine������ y,z�࿡ �־��ְ� 500�� ���� ���� �������� ���� �����ش�
	retVector = boss->GetActorLocation() + FVector(0,500 * c, 500 * s);
	// ����(Bullet)�� ��ġ�� �ϼ��� ���ͺ���(���������� ����)�� �־��ش�
	SetActorLocation(retVector);
}

