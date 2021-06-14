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
	// �귯���ð� * �ӷ� = �ӵ�
	theta += GetWorld()->RealTimeSeconds * 5;
}


// Called every frame
void UBossShield::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	//Playing��尡 �ƴҽ� ����
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	//����ð�
	currentTime += DeltaTime;
	//����ð��� ����ð��� �ʰ��ϸ�
	if (currentTime / 2 && currentTime > 5)
	{
		if (bulletFactory)
		{
			//�����ɶ� ������Ʈ�� ���ĵ� �����ϰ�
			FActorSpawnParameters pram;
			pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			//�ѱ���ġ���� �Ѿ˰��忡�� ������� �Ѿ��� �߻�
			auto bullet = GetWorld()->SpawnActor<ABossBulletCPP>(bulletFactory, me->firePosition->GetComponentLocation(), me->firePosition->GetComponentRotation(), pram);
			
			//sine = ������(z), cosine ������(y)�ȿ� �ӵ��� �־���
			float s = FMath::Sin(theta);
			float c = FMath::Cos(theta);

			//������(150)�ʱⰪ�� �ð��� ������ Ŀ���� Delta�� 200�� ���� ���� �����ش�.
			//helix += (DeltaTime * 200);

			//������� ���ͺ����ȿ� *������ ��ġ���� �������� sine,cosine������ y,z�࿡ �־��ְ� 500�� ���� ���� �������� ���� �����ش�
			retVector = me->GetActorLocation() + FVector(0, 500*c, 500*s);
			// ����(Bullet)�� ��ġ�� �ϼ��� ���ͺ���(���������� ����)�� �־��ش�
			bullet->SetActorLocation(retVector);
			//����ð� �ʱ�ȭ
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

