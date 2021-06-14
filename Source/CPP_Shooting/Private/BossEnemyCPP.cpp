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

	//��ü
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	//boxComp�� ��Ʈ������Ʈ��
	RootComponent = boxComp;
	//�ܰ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//��Ʈ�� �ڽ�����
	meshComp->SetupAttachment(boxComp);
	//�ܰ��� �浹ü ����
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//�ѱ�
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	//��Ʈ�� �ڽ�����
	firePosition->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ABossEnemyCPP::BeginPlay()
{
	Super::BeginPlay();
	
	boxComp->OnComponentHit.AddDynamic(this, &ABossEnemyCPP::OnColliderEnter);
}

// 1 ������ ���۵Ǹ� 2�ʰ� �� ����
// 2 ���� ������ �� 3�ʰ� ������ �߻�
// 3 ������ �߻� �� 2�� �� 3�ʰ� �������� 
void ABossEnemyCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	//Playing��尡 �ƴҽ� ����
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}
	//����ð�
	currentTime += DeltaTime;
	//����ð��� ����ð��� �ʰ��ϸ�
	if (currentTime / 2)
	{
		//��
		if (shieldFactory)
		{
			//�����ɶ� ������Ʈ�� ���ĵ� �����ϰ�
			FActorSpawnParameters pram;
			pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			//�ѱ���ġ���� �Ѿ˰��忡�� ������� �Ѿ��� �߻�
			GetWorld()->SpawnActor<ABossShieldCPP>(shieldFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation(), pram);
			//����ð� �ʱ�ȭ
			if (currentTime > 2)
			{
				for (TActorIterator<ABossShieldCPP> it(GetWorld()); it; ++it)
				{
					it->Destroy();
				}
			}
		}
		//�������߻�
		if (bulletFactory && currentTime >= 3)
		{
			//�����ɶ� ������Ʈ�� ���ĵ� �����ϰ�
			FActorSpawnParameters pram;
			pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			//�ѱ���ġ���� �Ѿ˰��忡�� ������� �Ѿ��� �߻�
			GetWorld()->SpawnActor<ABossBulletCPP>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation(), pram);
			//����ð� �ʱ�ȭ
			if (currentTime > 6)
			{
				for (TActorIterator<ABossBulletCPP> it(GetWorld()); it; ++it)
				{
					it->Destroy();
				}
			}
		}
		//�������� �߻�
		if (helixFactory && currentTime >= 8)
		{
			//�����ɶ� ������Ʈ�� ���ĵ� �����ϰ�
			FActorSpawnParameters pram;
			pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			//�ѱ���ġ���� �Ѿ˰��忡�� ������� �Ѿ��� �߻�
			GetWorld()->SpawnActor<ABossHelixCPP>(helixFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation(), pram);
			//����ð� �ʱ�ȭ
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

	//test �̵�
	//SetActorLocation(GetActorLocation() + FVector(0, 0, -1) * 100 * DeltaTime);
}

void ABossEnemyCPP::OnColliderEnter(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//bullet�� ������ �޾ƿ´�
	auto bullet = Cast<ABulletCPP>(OtherActor);
	//GameMode�� �޾ƿ´�
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	//����ڵ�
	if (bullet == nullptr)
	{
		return;
	}
	//�ε��� Actor�� Bullet�̶��
	if (OtherActor == bullet)
	{
		//���� Ƚ���� 1�ø���
		point +=1;
		//�ҷ��� źâ�� �־��ش�
		gameMode->AddBullet(bullet);
		//20���̻� �´´ٸ�
		if (point == 20)
		{
			//����ȿ��,���߻���
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), expolsionFactory, GetActorLocation());
			UGameplayStatics::SpawnSound2D(GetWorld(), expolsionSound);
			//�״´�
			Destroy();
			//���� Ƚ�� �ʱ�ȭ
			point = 0;
		}
	}
}

