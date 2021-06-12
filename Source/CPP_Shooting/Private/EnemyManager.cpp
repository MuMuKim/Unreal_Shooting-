// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "CPP_ShootingGameModeBase.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// GameMode�� State�� Playing�� �ƴ϶�� �Ʒ� �ڵ�� ������� �ʵ��� �ϰ� �ʹ�.
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	crruntTime += DeltaTime;
	if (crruntTime >= createTime)
	{
		//���鶧 ���ڸ��� �ٸ� �༮�� �ִ��� ����������� ���� ex.�����ڸ��� ���� �ִٸ� ������ �ȵ�.
		FActorSpawnParameters Param;
		//Collision�� �ִ��� ����
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//GetWord�� ��������� ������
		GetWorld()->SpawnActor<AEnemyCPP>(EnemyFactory,
			GetActorLocation(),
			GetActorRotation(), Param);
		crruntTime = 0;
	}
}
