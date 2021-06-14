// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CPP_Shooting.h"
#include "GameFramework/GameModeBase.h"
#include "BulletCPP.h"
#include "PlayerCPP.h"
#include <Blueprint/UserWidget.h>
#include "CPP_ShootingGameModeBase.generated.h"

//델리게이트 만들기
DECLARE_DELEGATE_OneParam(FPlayingStateDelegate,float value)

//총알 오브젝트풀을 위한 속성 선언
//필요속성 : 탄창크기, 탄창(오브젝트풀), 총알공장

//게임의 상태제어
// ->Ready, Playing, GameOver
//열거형
UENUM(BluePrintType)//BluePrintType을 넣으면 BP에서 쓸수있다
enum class EGameState : uint8
{
	
	// 0부터 순서대로 할당 (중간에 숫자를 크게바꾸면 그다음 숫자는 전숫자의 +1)
	Ready UMETA(ThisPlayName = "READY_STATE"), 
	Playing UMETA(ThisPlayName = "Playing_STATE"),
	GameOver UMETA(ThisPlayName = "GameOver_STATE")
};
UCLASS()
class CPP_SHOOTING_API ACPP_ShootingGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACPP_ShootingGameModeBase();

	FPlayingStateDelegate OnPlayingStateDelegate;

	UFUNCTION()
	void PlayingProcess(float value);

	//게임이 초기화 될 때 호출됨
	//GameMode가 제공해주는 함수(Begin보다 먼저호출)
	virtual void InitGameState() override;

	//Begin 함수추가
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void ReadyPage(float DeltaSeconds);
	void PlayingPage();
	void GameOverPage();

	//총알 활성화 시키는 함수
	void SetbulletActive(ABulletCPP* bullet, bool isActive);

	//탄창에 총알을 추가해주는 함수
	void AddBullet(ABulletCPP* bullet);

	//탄창에서 총알을 하나 빼오기
	ABulletCPP* GetBullet();

	//Bullet을 만드는 함수
	ABulletCPP* CreateBullet();

	//Screen에 상태를 보여주기 위한 함수(선언):BluePrint에서 함수를 구현하도록 설정
	UFUNCTION(BlueprintImplementableEvent, Category = "PrintLog")
	void PrintEnumDeta(EGameState value);

	//Private의 캡슐화된 변수를 불러오는 함수
	EGameState GetState()
	{
		return mstate;
	}
	//상태를 바꾸는 함수
	void SetState(EGameState s);

	//Player공장
	UPROPERTY(EditDefaultsOnly, Category = "PlayerClass")
	TSubclassOf<class APlayerCPP> PlayerFactory;


private:
	//상태변수
	//->BP에 노출시키고 싶다 하지만 Private이라 안됌
	//->meta =(AllowPrivateAccess = ture)를 쓰면 Private이여도 노출가능(유니티 씨리얼라이즈필드)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = ture))
	EGameState mstate = EGameState::Ready;
	//필요속성 : 탄창크기, 탄창(오브젝트풀), 총알공장
	UPROPERTY(EditDefaultsOnly, Category = "Bullet", meta = (AllowPrivateAccess = ture))
	int bulletPoolSize = 20;

	UPROPERTY(VisibleAnywhere, Category = "Bullet", meta = (AllowPrivateAccess = ture))
	TArray<ABulletCPP*>	bulletPool;

	//공장
	UPROPERTY(EditDefaultsOnly, Category = "BulletClass", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class ABulletCPP> bulletFactory;

	//State Ready에 필요한 속성 : 일정시간, 경과시간
	UPROPERTY(EditAnywhere, Category = "State", meta = (AllowPrivateAccess = ture))
	float readyDelyTime = 2;
	UPROPERTY()
	float curruntTime = 0;
	//--------------------------------------------------------------------------
	//Ready Widjet BP 공장 선언
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> readyUIFactory;
	//Ready Ui를 재활용 하기위해 속성으로 등록해 사용
	UPROPERTY()
	class UUserWidget* readyUI;

	//Start Widjet BP 공장 선언
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> startUIFactory;
	//Start Ui를 재활용 하기위해 속성으로 등록해 사용
	UPROPERTY()
	class UUserWidget* startUI;

	//GameOver Ui를 재활용 하기위해 속성으로 등록해 사용
	UPROPERTY()
	class UUserWidget* gameOverUI;
	//GameOver Widjet BP 공장 선언
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> gameOverUIFactory;

	//현재점수
	int32 curScore = 0;
	//최고점수
	int32 topScore = 0;

	//User Widget -> Score UI
	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> scoreUIFactory;

	//ScoreUi 공장에서 만들어진 scoreUi를 기억할 변수
	UPROPERTY()
	class UScoreCPP* scoreUI;

	//SaveGame 인스턴스를 변수로 기억
	UPROPERTY()
	class USaveData* saveData;
	
public:
	// 현재점수를 넣을 때 쓰는 함수
	void SetCurrentScore(int32 point);
	// 현재점수를 불러올 때 쓰는 함수
	int32 GetCurrentScore();
};
