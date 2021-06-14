// Copyright Epic Games, Inc. All Rights Reserved.


#include "CPP_ShootingGameModeBase.h"
#include "CPP_Shooting.h"
#include "EnemyCPP.h"
#include <Kismet/GameplayStatics.h>
#include <EngineUtils.h>
#include <GameFramework/Actor.h>
#include <Engine/World.h>
#include <Blueprint/UserWidget.h>
#include "ScoreCPP.h"
#include "SaveData.h"


ACPP_ShootingGameModeBase::ACPP_ShootingGameModeBase()
{
	//Tick�Լ��� ��� ȣ��ǵ��� ����
	PrimaryActorTick.bCanEverTick = true;

	//����Ʈ Pawn�� Player�� �����Ǿ��ִ�.
	DefaultPawnClass = NULL;
}

void ACPP_ShootingGameModeBase::PlayingProcess(float value)
{
	//Start UI�� ���ش�
	startUI->RemoveFromViewport();
	curruntTime = value;
}

void ACPP_ShootingGameModeBase::InitGameState()
{
	Super::InitGameState();

	//1 ȭ�鿡 Enemy�� �ִٸ� �� �������ִ� 2���� ���
	//Enmey�� ���� ����Ʈ ��׸��� ����
	//TArray<AActor*> objs; 
	// ���忡�� Enemy�� ã�Ƽ� AEnemyCPP::StaticClass()�� ���� AEnemyŸ������ ��׸�(objs)�� �����
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCPP::StaticClass(), objs);
	////for���� ���� objs�� ��� Enemy���ڸ�ŭ ���� �������ش�.
	//for (auto obj : objs)
	//{
	//	AEnemyCPP* enemy = Cast<AEnemyCPP>(obj);
	//	enemy->Destroy();
	//	//objs->Destroy();
	//}
	
	/*�ڷ��� ������ ()�� ���� �����ڸ� ȣ���ؿü��ִ�.
	TActorInerator<AEnemy> it(GetWorld())
	����� it;�� ù��°�ּ�(�����ּ�)�� �� �����Ͱ� �ִ��� Ȯ��(ture���� ����), ++it�� ���� �ּҷ� �Ѿ�� ��
	���� : ����󿡼� AEnemy�� �� �ܾ�´� - �����ּҺ��� �� ũ�⸸ŭ ����*/
	for (TActorIterator<AEnemyCPP> it(GetWorld()); it; ++it)
	{
		UE_LOG(LogTemp,Warning,TEXT("EnemyActor : %s"), *it->GetName());
		it->Destroy();
	}

	//2 ȭ�鿡 �Ѿ��� ������ �� Ǯ���ش�
	//->1 ȭ�鿡 �ִ� �Ѿ˵��� ã�� �̾Ƴ� ������ �־��ش�
	for (TActorIterator<ABulletCPP> it(GetWorld()); it; ++it)
	{
		//->2 for���� ���� �ϳ��� GameModeBase�� ADDBullet�Լ��� �־��ش�
		ABulletCPP* bullet = *it;
		AddBullet(bullet);
		//AddBullet(*it);;
	}

	//3 Player�� ������ ������ش�
	//->1 ����� Player�� ã�ƺ���
	auto playerobj = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCPP::StaticClass());
	//->2 ���� ����� Player�� ���ٸ�
	// ��� GameOver�� �Ǿ��ٸ� ������ Player�� ���� ������ ���ǿ� GameOver���� Ȯ�θ� ���ָ� ��.
	if (mstate == EGameState::GameOver && playerobj == nullptr) 
	{
		//->3 Player�� ����� �ʹ�
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//PlayerFctory�� �����ʿ� ���� DefaultPawnClass�� �־��ָ� ��.
		 auto ctrl = GetWorld()->SpawnActor<APlayerCPP>(PlayerFactory,
														FVector::ZeroVector,
														FRotator::ZeroRotator, Param);

		//�������� �ٽ� ��� ���� Spawn���� Actor���� Possess(����)���ش�
		GetWorld()->GetFirstPlayerController()->Possess(ctrl);
	}
	//4 ���¸� Ready �� ��ȯ���ش�
	mstate = EGameState::Ready;

	//readyUI�� �ִٸ� Ready UI ȭ�鿡 ���
	//->reset ��ư�� ������ ��
	if (readyUI)
	{
		//ȭ�鿡 UI���̰� �ϱ�
		readyUI->AddToViewport();
	}

	//ȭ�鿡 �ִ� GameOver UI�� �����ϰ� �ʹ�
	//->reset ��ư�� ������ ��
	if (gameOverUI)
	{
		gameOverUI->RemoveFromViewport();
	}

	//-----------------------------------------------------------------------------
	//������ �ε��ϱ�

	//SaveData �ε��ϱ�
	saveData = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("TopScore"),0));
	
	//->���� ���� �����Ͱ� ������
	if (saveData == nullptr)
	{
		//saveData �ϳ��� �����
		auto saveGame = UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass());
		saveData = Cast<USaveData>(saveGame);
		saveData->topScore = 0;
		//���彽��
		UGameplayStatics::SaveGameToSlot(saveData, TEXT("TopScore"), 0);
		
	}
	//->topScore�� �ε�� ������ �Ҵ�
	topScore = saveData->topScore;
	if (scoreUI)
	{
		//UI�� topScore ���
		scoreUI->PrintTopScore(topScore);
		scoreUI->PrintCurrentScore(curScore);
	}

}

void ACPP_ShootingGameModeBase::BeginPlay() //������� = 1
{
	Super::BeginPlay(); // �ٸ����͵��� Begin�� ȣ���ϱ� ������ �θ��� Begin�� ȣ���������

	//�Լ� ��������Ʈ�� ���� ó���Ҵ��(this) ������Ʈ�� �Լ��� �������ִ� �ǹ�
	OnPlayingStateDelegate.BindUObject(this, &ACPP_ShootingGameModeBase::PlayingProcess);

	//����ڵ� (�Ѿ� ���� �ּҰ� �ִٸ�)
	if (bulletFactory)
	{
		// źâ�� �Ѿ� ����� ����
		for (int32 i = 0; i < bulletPoolSize; ++i)
		{
			// �Ѿ˰��忡�� �Ѿ��� �����
			ABulletCPP* bullet = CreateBullet();

			// źâ�� �Ѿ��� �ִ´�
			AddBullet(bullet);
		}
	}
	

	// �¾ �� Ready UI�����
	//����ڵ�(Null�� �ƴ϶��)
	if (readyUIFactory)
	{
		//Ready UI�� ����� �ʹ�
		readyUI = CreateWidget<UUserWidget>(GetWorld(), readyUIFactory);

		//ȭ�鿡 UI���̰� �ϱ�
		readyUI->AddToViewport();
	}

	// Start UI�����
	//����ڵ�(Null�� �ƴ϶��)
	if (startUIFactory)
	{
		//Ready UI�� ����� �ʹ�
		startUI = CreateWidget<UUserWidget>(GetWorld(), startUIFactory);
	}

	// GameOver UI�����
	//����ڵ�(Null�� �ƴ϶��)
	if (gameOverUIFactory)
	{
		//Ready UI�� ����� �ʹ�
		gameOverUI = CreateWidget<UUserWidget>(GetWorld(), gameOverUIFactory);
	}

	//Socre UI�� �����ϰ� �������
	scoreUI = CreateWidget<UScoreCPP>(GetWorld(), scoreUIFactory);
	if (scoreUI)
	{
		scoreUI->AddToViewport();
		//curScore�� ó�� 0���� ��µǰ� ���
		scoreUI->PrintCurrentScore(curScore);
		//topScore�� UI�� ���
		scoreUI->PrintTopScore(topScore);
	}
}

void ACPP_ShootingGameModeBase::Tick(float DeltaSeconds)
{
	// Enum�� ������¸� ����غ��� �ʹ�
	/*const UEnum* enumptr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGameState"), true);
	if (enumptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("State : %s"), *enumptr->GetNameStringByValue((uint8)mstate);
	}*/

	//ȭ�鿡 ���¸� ����ϰ� �ʹ�.
	//PrintEnumDeta(mstate);

	//��������
	switch (mstate)
	{
	case EGameState::Ready:
		ReadyPage(DeltaSeconds);
		break;
	case EGameState::Playing:
		PlayingPage();
		break;
	case EGameState::GameOver:
		GameOverPage();
		break;
	}
}

//�����ð� ��ٷȴٰ� ���¸� Playing���� ��ȯ�ϰ� �ʹ�
// ->Ready �ؽ�Ʈ ǥ���ϱ� log
//�ʿ�Ӽ�:
void ACPP_ShootingGameModeBase::ReadyPage(float DeltaSeconds)
{
	UE_LOG(LogTemp, Warning, TEXT("READY STATE"));

	

	//1 �ð��� �帣�� ������
	//Delta�� �������� 2����
	//curruntTime += GetWorld()->DeltaTimeSeconds; 
	curruntTime += DeltaSeconds; // �ش����Ͽ��� �������� �� float Delta�� �޾��ְ� ������ְ�, Tick�Լ����� ���� �Լ��� �θ� �� ���ڰ����� Delta�� ���´�.
	//2 ����ð��� �ʰ��ߴٸ�
	if (readyDelyTime < curruntTime)
	{
		//3 Playing�Լ��� �̵�
		mstate = EGameState::Playing; //Switch�� mstate�� �ٲ��ش�
		curruntTime = 0;

		//ȭ�鿡 �ִ� Ready UI�� �����ϰ� �ʹ�
		if (readyUI)
		{
			readyUI->RemoveFromViewport();
		}
		//Start�� ȭ�鿡 ���̰� ����
		if (startUI)
		{
			//ȭ�鿡 UI���̰� �ϱ�
			startUI->AddToViewport();
		}
	}
}
//Start �ؽ�Ʈ ǥ���ϱ�
//Start �ؽ�Ʈ�� 2���� �����
//������ �����ϰ� �Ѵ�
void ACPP_ShootingGameModeBase::PlayingPage()
{
	UE_LOG(LogTemp, Warning, TEXT("Playing STATE"));

	//�ð��� �帥��
	curruntTime += GetWorld()->GetDeltaSeconds();
	// ����ð��� ����ð� �̻��� �ȴٸ�
	if (curruntTime >= 1)
	{
		OnPlayingStateDelegate.ExecuteIfBound(0);
	}
}
//GameOver �޴��� ǥ��
//RŰ�� ������ �ٽ� �����ϱ�
void ACPP_ShootingGameModeBase::GameOverPage()
{
	UE_LOG(LogTemp, Warning, TEXT("GameOver STATE"));
	
	//PlayerController ��������
	APlayerController* myController = GetWorld()->GetFirstPlayerController(); //Player 0
	// myController�� �ְ�(����ڵ�) RŰ�� �����ٸ�
	if (myController && myController->WasInputKeyJustPressed(EKeys::R))
	{
		UE_LOG(LogTemp, Warning, TEXT("R key!!!!!!!!!!!!!!!!!!!!!"));
		ResetLevel();
	}
}

//�Ѿ� Ȱ��ȭ ��Ű�� �Լ�
void ACPP_ShootingGameModeBase::SetbulletActive(ABulletCPP* bullet, bool isActive) //������� = 4
{
	//isActive�� ó���� False�� �޾ұ� ������
	bullet->SetActorHiddenInGame(!isActive); //�Ѿ��� (!=��)���̰�
	bullet->SetActorEnableCollision(isActive); //�Ѿ��� �浹���ϰ�
	bullet->SetActorTickEnabled(isActive); //�Ѿ��� ��������ʰ�
}

//źâ�� �Ѿ��� �߰����ִ� �Լ�
void ACPP_ShootingGameModeBase::AddBullet(ABulletCPP* bullet) //������� = 3
{
	// źâ�� �Ѿ��� �ִ´�
	bulletPool.AddUnique(bullet); //�������� �����ʴ� ADDUnique

	// �Ѿ��� ��Ȱ��ȭ ��Ų��
	SetbulletActive(bullet, false);
}

ABulletCPP* ACPP_ShootingGameModeBase::CreateBullet() //������� = 2
{
	FActorSpawnParameters pram;
	//�����Ǵ� ��ġ�� �ٸ����Ͱ� �ִ��� ������Ų��
	pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//���ӸŴ���(GetWorld)�ȿ� �ִ� �������ͱ�ɿ� ������ ���ڰ����� ��ġ�� �������ְ� pram�̶� ������ �߰�
	auto bullet = GetWorld()->SpawnActor<ABulletCPP>(bulletFactory, FVector::ZeroVector, FRotator::ZeroRotator, pram);

	return bullet;
}

void ACPP_ShootingGameModeBase::SetState(EGameState s)
{
	mstate = s;

	if (mstate == EGameState::GameOver)
	{
		//���� �Ͻ�����
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		//���콺Ŀ���� ���̰� �Ѵ�
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		//GameOver UI�� ����
		gameOverUI->AddToViewport();
	}
}

// źâ���� �Ѿ� ������
ABulletCPP* ACPP_ShootingGameModeBase::GetBullet() //������� = 5
{
	/*
	// �迭�� ���� �ϳ� �̸��̶�� Null�� ��ȯ
	if (bulletPool.Num() < 1)
	{
		return nullptr;
	}
	//Ǯ���� �Ѿ��� �ϳ� ������ �ʹ�
	ABulletCPP* bullet = bulletPool[0];
	//źâ���� ���� �Ѿ� ���ֱ�
	//->RemoveAt
	bulletPool.RemoveAt(0);
	//�Ѿ��� ��ȯ���ֱ�
	return bullet;
	*/

	ABulletCPP* bullet = bulletPool.Pop();
	return bullet;
}

void ACPP_ShootingGameModeBase::SetCurrentScore(int32 point)
{
	//��������
	curScore = point;
	//UI�� ǥ���ϰ� �ʹ�
	//->Socre UI Widget �� ���� �Ҵ��Ű��ʹ�
	scoreUI->PrintCurrentScore(curScore);

	// TopScore�� ���� ������ �ǳ�?
	//->���������� �ְ������� �Ѿ��
	if (topScore < curScore)
	{
		//->���������� �ְ������� �ȴ�
		topScore = curScore;
		//TopScore ����
		scoreUI->PrintTopScore(topScore);

		//�����͸� �����ؾ��Ѵ�
		saveData->topScore = topScore;
		UGameplayStatics::SaveGameToSlot(saveData, TEXT("TopScore"),0);
	}
}

int32 ACPP_ShootingGameModeBase::GetCurrentScore()
{
	return curScore;
}

