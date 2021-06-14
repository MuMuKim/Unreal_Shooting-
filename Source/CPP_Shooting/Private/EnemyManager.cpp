// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "CPP_ShootingGameModeBase.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
	//타이머 맞추기
	GetWorld()->GetTimerManager().SetTimer(createTimer, this, &AEnemyManager::CreateEnemy,createTime, true, 0);
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// GameMode의 State가 Playing이 아니라면 아래 코드는 실행되지 않도록 하고 싶다.

	/*auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	crruntTime += DeltaTime;
	if (crruntTime >= createTime)
	{
		//만들때 그자리에 다른 녀석이 있더라도 만들어지도록 설정 ex.생성자리에 무언가 있다면 생성이 안됨.
		FActorSpawnParameters Param;
		//Collision이 있더라도 생성
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//GetWord는 가상공간을 관리함
		GetWorld()->SpawnActor<AEnemyCPP>(EnemyFactory,
			GetActorLocation(),
			GetActorRotation(), Param);
		crruntTime = 0;
	}*/
}

void AEnemyManager::CreateEnemy()
{
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	/*if (gameMode->GetState() != EGameState::GameOver)
	{
		//타이머 끄기
		GetWorld()->GetTimerManager().ClearTimer(createTimer);
	}*/

	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}

	//만들때 그자리에 다른 녀석이 있더라도 만들어지도록 설정 ex.생성자리에 무언가 있다면 생성이 안됨.
	FActorSpawnParameters Param;
	//Collision이 있더라도 생성
	Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//GetWord는 가상공간을 관리함
	GetWorld()->SpawnActor<AEnemyCPP>(EnemyFactory,
		GetActorLocation(),
		GetActorRotation(), Param);
}



