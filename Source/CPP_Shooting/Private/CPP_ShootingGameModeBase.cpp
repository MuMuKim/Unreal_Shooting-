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
	//Tick함수가 계속 호출되도록 설정
	PrimaryActorTick.bCanEverTick = true;

	//디폴트 Pawn은 Player로 설정되어있다.
	DefaultPawnClass = NULL;
}

void ACPP_ShootingGameModeBase::PlayingProcess(float value)
{
	//Start UI를 꺼준다
	startUI->RemoveFromViewport();
	curruntTime = value;
}

void ACPP_ShootingGameModeBase::InitGameState()
{
	Super::InitGameState();

	//1 화면에 Enemy가 있다면 다 제거해주는 2가지 방법
	//Enmey를 담을 리스트 빈그릇을 만듬
	//TArray<AActor*> objs; 
	// 월드에서 Enemy를 찾아서 AEnemyCPP::StaticClass()를 통해 AEnemy타입으로 빈그릇(objs)에 담아줌
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyCPP::StaticClass(), objs);
	////for문을 통해 objs에 담긴 Enemy숫자만큼 돌아 제거해준다.
	//for (auto obj : objs)
	//{
	//	AEnemyCPP* enemy = Cast<AEnemyCPP>(obj);
	//	enemy->Destroy();
	//	//objs->Destroy();
	//}
	
	/*자료형 변수명 ()를 쓰면 생성자를 호출해올수있다.
	TActorInerator<AEnemy> it(GetWorld())
	가운데에 it;는 첫번째주소(시작주소)로 들어가 데이터가 있는지 확인(ture여야 실행), ++it는 다음 주소로 넘어가는 뜻
	정리 : 월드상에서 AEnemy를 싹 긁어온다 - 시작주소부터 방 크기만큼 돈다*/
	for (TActorIterator<AEnemyCPP> it(GetWorld()); it; ++it)
	{
		UE_LOG(LogTemp,Warning,TEXT("EnemyActor : %s"), *it->GetName());
		it->Destroy();
	}

	//2 화면에 총알이 있으면 다 풀해준다
	//->1 화면에 있는 총알들을 찾아 뽑아내 변수에 넣어준다
	for (TActorIterator<ABulletCPP> it(GetWorld()); it; ++it)
	{
		//->2 for문을 통해 하나씩 GameModeBase의 ADDBullet함수에 넣어준다
		ABulletCPP* bullet = *it;
		AddBullet(bullet);
		//AddBullet(*it);;
	}

	//3 Player가 없으면 만들어준다
	//->1 월드상에 Player를 찾아본다
	auto playerobj = UGameplayStatics::GetActorOfClass(GetWorld(), APlayerCPP::StaticClass());
	//->2 만약 월드상에 Player가 없다면
	// 사실 GameOver가 되었다면 무조건 Player는 없기 때문에 조건에 GameOver인지 확인만 해주면 됨.
	if (mstate == EGameState::GameOver && playerobj == nullptr) 
	{
		//->3 Player를 만들고 싶다
		FActorSpawnParameters Param;
		Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//PlayerFctory를 해줄필요 없이 DefaultPawnClass를 넣어주면 됌.
		 auto ctrl = GetWorld()->SpawnActor<APlayerCPP>(PlayerFactory,
														FVector::ZeroVector,
														FRotator::ZeroRotator, Param);

		//조종권을 다시 얻기 위해 Spawn해준 Actor에게 Possess(빙의)해준다
		GetWorld()->GetFirstPlayerController()->Possess(ctrl);
	}
	//4 상태를 Ready 로 전환해준다
	mstate = EGameState::Ready;

	//readyUI가 있다면 Ready UI 화면에 출력
	//->reset 버튼을 눌렀을 때
	if (readyUI)
	{
		//화면에 UI보이게 하기
		readyUI->AddToViewport();
	}

	//화면에 있는 GameOver UI를 제거하고 싶다
	//->reset 버튼을 눌렀을 때
	if (gameOverUI)
	{
		gameOverUI->RemoveFromViewport();
	}

	//-----------------------------------------------------------------------------
	//데이터 로드하기

	//SaveData 로드하기
	saveData = Cast<USaveData>(UGameplayStatics::LoadGameFromSlot(TEXT("TopScore"),0));
	
	//->만약 저장 데이터가 없으면
	if (saveData == nullptr)
	{
		//saveData 하나를 만든다
		auto saveGame = UGameplayStatics::CreateSaveGameObject(USaveData::StaticClass());
		saveData = Cast<USaveData>(saveGame);
		saveData->topScore = 0;
		//저장슬롯
		UGameplayStatics::SaveGameToSlot(saveData, TEXT("TopScore"), 0);
		
	}
	//->topScore에 로드된 데이터 할당
	topScore = saveData->topScore;
	if (scoreUI)
	{
		//UI에 topScore 출력
		scoreUI->PrintTopScore(topScore);
		scoreUI->PrintCurrentScore(curScore);
	}

}

void ACPP_ShootingGameModeBase::BeginPlay() //실행순서 = 1
{
	Super::BeginPlay(); // 다른액터들의 Begin을 호출하기 때문에 부모의 Begin을 호출해줘야함

	//함수 델리게이트와 연결 처리할대상(this) 오브젝트와 함수를 연결해주는 의미
	OnPlayingStateDelegate.BindUObject(this, &ACPP_ShootingGameModeBase::PlayingProcess);

	//방어코드 (총알 공장 주소가 있다면)
	if (bulletFactory)
	{
		// 탄창에 총알 만들어 넣자
		for (int32 i = 0; i < bulletPoolSize; ++i)
		{
			// 총알공장에서 총알을 만든다
			ABulletCPP* bullet = CreateBullet();

			// 탄창에 총알을 넣는다
			AddBullet(bullet);
		}
	}
	

	// 태어날 때 Ready UI만들기
	//방어코드(Null이 아니라면)
	if (readyUIFactory)
	{
		//Ready UI를 만들고 싶다
		readyUI = CreateWidget<UUserWidget>(GetWorld(), readyUIFactory);

		//화면에 UI보이게 하기
		readyUI->AddToViewport();
	}

	// Start UI만들기
	//방어코드(Null이 아니라면)
	if (startUIFactory)
	{
		//Ready UI를 만들고 싶다
		startUI = CreateWidget<UUserWidget>(GetWorld(), startUIFactory);
	}

	// GameOver UI만들기
	//방어코드(Null이 아니라면)
	if (gameOverUIFactory)
	{
		//Ready UI를 만들고 싶다
		gameOverUI = CreateWidget<UUserWidget>(GetWorld(), gameOverUIFactory);
	}

	//Socre UI를 생성하고 등록하자
	scoreUI = CreateWidget<UScoreCPP>(GetWorld(), scoreUIFactory);
	if (scoreUI)
	{
		scoreUI->AddToViewport();
		//curScore가 처음 0으로 출력되게 출력
		scoreUI->PrintCurrentScore(curScore);
		//topScore를 UI에 출력
		scoreUI->PrintTopScore(topScore);
	}
}

void ACPP_ShootingGameModeBase::Tick(float DeltaSeconds)
{
	// Enum의 현재상태를 출력해보고 싶다
	/*const UEnum* enumptr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGameState"), true);
	if (enumptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("State : %s"), *enumptr->GetNameStringByValue((uint8)mstate);
	}*/

	//화면에 상태를 출력하고 싶다.
	//PrintEnumDeta(mstate);

	//상태제어
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

//일정시간 기다렸다가 상태를 Playing으로 전환하고 싶다
// ->Ready 텍스트 표현하기 log
//필요속성:
void ACPP_ShootingGameModeBase::ReadyPage(float DeltaSeconds)
{
	UE_LOG(LogTemp, Warning, TEXT("READY STATE"));

	

	//1 시간이 흐르는 변수가
	//Delta를 가져오는 2가지
	//curruntTime += GetWorld()->DeltaTimeSeconds; 
	curruntTime += DeltaSeconds; // 해더파일에서 선언해줄 때 float Delta를 받아주게 만들어주고, Tick함수에서 현재 함수를 부를 때 인자값으로 Delta를 적는다.
	//2 경과시간을 초과했다면
	if (readyDelyTime < curruntTime)
	{
		//3 Playing함수로 이동
		mstate = EGameState::Playing; //Switch의 mstate를 바꿔준다
		curruntTime = 0;

		//화면에 있는 Ready UI를 제거하고 싶다
		if (readyUI)
		{
			readyUI->RemoveFromViewport();
		}
		//Start가 화면에 보이게 하자
		if (startUI)
		{
			//화면에 UI보이게 하기
			startUI->AddToViewport();
		}
	}
}
//Start 텍스트 표현하기
//Start 텍스트는 2초후 사라짐
//게임을 동작하게 한다
void ACPP_ShootingGameModeBase::PlayingPage()
{
	UE_LOG(LogTemp, Warning, TEXT("Playing STATE"));

	//시간이 흐른다
	curruntTime += GetWorld()->GetDeltaSeconds();
	// 현재시간이 경과시간 이상이 된다면
	if (curruntTime >= 1)
	{
		OnPlayingStateDelegate.ExecuteIfBound(0);
	}
}
//GameOver 메뉴를 표현
//R키를 누르면 다시 시작하기
void ACPP_ShootingGameModeBase::GameOverPage()
{
	UE_LOG(LogTemp, Warning, TEXT("GameOver STATE"));
	
	//PlayerController 가져오기
	APlayerController* myController = GetWorld()->GetFirstPlayerController(); //Player 0
	// myController가 있고(방어코드) R키를 눌렀다면
	if (myController && myController->WasInputKeyJustPressed(EKeys::R))
	{
		UE_LOG(LogTemp, Warning, TEXT("R key!!!!!!!!!!!!!!!!!!!!!"));
		ResetLevel();
	}
}

//총알 활성화 시키는 함수
void ACPP_ShootingGameModeBase::SetbulletActive(ABulletCPP* bullet, bool isActive) //실행순서 = 4
{
	//isActive를 처음엔 False로 받았기 때문에
	bullet->SetActorHiddenInGame(!isActive); //총알을 (!=안)보이게
	bullet->SetActorEnableCollision(isActive); //총알이 충돌안하게
	bullet->SetActorTickEnabled(isActive); //총알이 실행되지않게
}

//탄창에 총알을 추가해주는 함수
void ACPP_ShootingGameModeBase::AddBullet(ABulletCPP* bullet) //실행순서 = 3
{
	// 탄창에 총알을 넣는다
	bulletPool.AddUnique(bullet); //같은놈은 넣지않는 ADDUnique

	// 총알을 비활성화 시킨다
	SetbulletActive(bullet, false);
}

ABulletCPP* ACPP_ShootingGameModeBase::CreateBullet() //실행순서 = 2
{
	FActorSpawnParameters pram;
	//생성되는 위치에 다른액터가 있더라도 생성시킨다
	pram.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//게임매니저(GetWorld)안에 있는 스폰액터기능에 접근해 인자값으로 위치를 지정해주고 pram이란 조건을 추가
	auto bullet = GetWorld()->SpawnActor<ABulletCPP>(bulletFactory, FVector::ZeroVector, FRotator::ZeroRotator, pram);

	return bullet;
}

void ACPP_ShootingGameModeBase::SetState(EGameState s)
{
	mstate = s;

	if (mstate == EGameState::GameOver)
	{
		//게임 일시정지
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		//마우스커서를 보이게 한다
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		//GameOver UI를 띄운다
		gameOverUI->AddToViewport();
	}
}

// 탄창에서 총알 빼오기
ABulletCPP* ACPP_ShootingGameModeBase::GetBullet() //실행순서 = 5
{
	/*
	// 배열에 값이 하나 미만이라면 Null을 반환
	if (bulletPool.Num() < 1)
	{
		return nullptr;
	}
	//풀에서 총알을 하나 빼오고 싶다
	ABulletCPP* bullet = bulletPool[0];
	//탄창에서 빼온 총알 없애기
	//->RemoveAt
	bulletPool.RemoveAt(0);
	//총알을 반환해주기
	return bullet;
	*/

	ABulletCPP* bullet = bulletPool.Pop();
	return bullet;
}

void ACPP_ShootingGameModeBase::SetCurrentScore(int32 point)
{
	//현재점수
	curScore = point;
	//UI에 표시하고 싶다
	//->Socre UI Widget 에 값을 할당시키고싶다
	scoreUI->PrintCurrentScore(curScore);

	// TopScore은 언제 갱신이 되나?
	//->현재점수가 최고점수를 넘어서면
	if (topScore < curScore)
	{
		//->현재점수가 최고점수가 된다
		topScore = curScore;
		//TopScore 갱신
		scoreUI->PrintTopScore(topScore);

		//데이터를 저장해야한다
		saveData->topScore = topScore;
		UGameplayStatics::SaveGameToSlot(saveData, TEXT("TopScore"),0);
	}
}

int32 ACPP_ShootingGameModeBase::GetCurrentScore()
{
	return curScore;
}

