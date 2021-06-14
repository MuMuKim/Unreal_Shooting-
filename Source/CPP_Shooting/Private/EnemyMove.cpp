// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMove.h"
#include <Kismet/GameplayStatics.h>
#include "PlayerCPP.h"
#include "EnemyCPP.h"
#include <Math/UnrealMathUtility.h>
#include <GameFramework/Actor.h>
#include "CPP_ShootingGameModeBase.h"

// Sets default values for this component's properties
UEnemyMove::UEnemyMove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyMove::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AEnemyCPP>(GetOwner());

	//������Ʈ �浹�� ����� �̺�Ʈ �Լ��� �����ϰ� �ʹ�.
	//�ʿ��Ѱ� :ó���� �̺�Ʈ �Լ�
	//->������Ʈ �浹�� ���ؼ��� AddDynamic�Լ��� �̿��ؾ��Ѵ�
	//->AddDynamic �Լ��� ���ڷ� ��ϵǴ� �Լ��� �ݵ�� UFUNCTION ��ũ�θ� ����ؾ��Ѵ�.
	//boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCPP::OnTriggerEnter);

	//TArray�� �𸮾� �迭.�����ȿ� ���� �ڷ����� �־���,�ּҸ� �޾ƾ���(���������ʱ�����)
	TArray<AActor*> objs; // Ÿ��(�÷��̾�)�� ���� �׸�
	//�����Ҵ� : �¾ �� Ÿ���� ã�� ����

	//����� Actor�� ã�Ƴֱ� (�迭�� ��ƾ���)
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCPP::StaticClass(), objs);

	//for ������ objs�˻�
	for (AActor* actor : objs) //actor��� �ӽú����� objs�� ��� �ڷḸŭ ���� �ִ´�
	{
		target = actor;
	}
	//���Ʒ��� ���� ��
	/*for (int i = 0; i < objs.Num(); i++)
	{
		target = objs[0];
	}*/

	//�Ʒ��� ����, 50%���ϸ� Ÿ�ٹ������� ����.
	//ó�� dir���� �Ʒ���������
	dir = FVector(0, 0, -1);

	//��������
	int32 ab = FMath::FRandRange(1, 100);

	//���� Ÿ�ٿ� ���� ����� ��� �ִٸ� 
	if (target != nullptr)
	{
		//���� Ȯ���� 50%���ϸ� Ÿ�ٹ���
		if (ab <= 50)
		{
			//dir���� Ÿ�� - me ������ Ÿ�ٹ����� ���Ѵ�
			dir = target->GetActorLocation() - me->GetActorLocation();
		}
	}
	
}

// Called every frame
void UEnemyMove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//���ⱸ�ϱ�
	// Ÿ���� �ְ�, Ÿ���� ��ȿ�ϴٸ�(Ÿ���� �׾��� �� ���������� ����)
	if (target && IsValid(target))
	{
		dir; //�¾ �� ���� �״��
	}
	else
	{
		//�Ʒ���
		dir = FVector(0, 0, -1);
	}
	dir.Normalize();

	FVector v = dir * 500;
	//������
	FVector P0 = me->GetActorLocation();
	FVector P = P0 + v * DeltaTime;
	me->SetActorLocation(P, true);
}

void UEnemyMove::OnCollisionEnter(AActor* OtherActor)
{
	//����ȿ�� ����
	//�ں��� ->���� Transform���� ex�� �ν��Ͻ��� ����� ���Ѷ�
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory,
		me->GetActorTransform());
	//����ȿ�� Sound
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	//�ε��� Actor�� Bullet�� ��� źâ�� �ٽ� �־�����
	//bullet �����ȿ� otherActor(��������)�� BulletŸ������ ����ȯ��Ų��.
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	auto bullet = Cast<ABulletCPP>(OtherActor);
	if (bullet) //Bullet�� �´ٸ�
	{
		//Bullet�� ���� �ڸ��� �־��ش�
		gameMode->AddBullet(bullet);
	}
	else
	{
		//�ε����༮�� Player�� 
		auto player = Cast<APlayerCPP>(OtherActor);
		if (player)
		{
			//GameOver�� �����ϰ�ʹ�
			gameMode->SetState(EGameState::GameOver);
		}
		OtherActor->Destroy(); //���װ�
	}

	//������ �÷�����
	gameMode->SetCurrentScore(gameMode->GetCurrentScore() + 1);

	me->Destroy(); //������ this����
}

