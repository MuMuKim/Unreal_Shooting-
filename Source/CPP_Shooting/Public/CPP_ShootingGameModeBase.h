// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CPP_Shooting.h"
#include "GameFramework/GameModeBase.h"
#include "BulletCPP.h"
#include "PlayerCPP.h"
#include <Blueprint/UserWidget.h>
#include "CPP_ShootingGameModeBase.generated.h"

//��������Ʈ �����
DECLARE_DELEGATE_OneParam(FPlayingStateDelegate,float value)

//�Ѿ� ������ƮǮ�� ���� �Ӽ� ����
//�ʿ�Ӽ� : źâũ��, źâ(������ƮǮ), �Ѿ˰���

//������ ��������
// ->Ready, Playing, GameOver
//������
UENUM(BluePrintType)//BluePrintType�� ������ BP���� �����ִ�
enum class EGameState : uint8
{
	
	// 0���� ������� �Ҵ� (�߰��� ���ڸ� ũ�Թٲٸ� �״��� ���ڴ� �������� +1)
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

	//������ �ʱ�ȭ �� �� ȣ���
	//GameMode�� �������ִ� �Լ�(Begin���� ����ȣ��)
	virtual void InitGameState() override;

	//Begin �Լ��߰�
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void ReadyPage(float DeltaSeconds);
	void PlayingPage();
	void GameOverPage();

	//�Ѿ� Ȱ��ȭ ��Ű�� �Լ�
	void SetbulletActive(ABulletCPP* bullet, bool isActive);

	//źâ�� �Ѿ��� �߰����ִ� �Լ�
	void AddBullet(ABulletCPP* bullet);

	//źâ���� �Ѿ��� �ϳ� ������
	ABulletCPP* GetBullet();

	//Bullet�� ����� �Լ�
	ABulletCPP* CreateBullet();

	//Screen�� ���¸� �����ֱ� ���� �Լ�(����):BluePrint���� �Լ��� �����ϵ��� ����
	UFUNCTION(BlueprintImplementableEvent, Category = "PrintLog")
	void PrintEnumDeta(EGameState value);

	//Private�� ĸ��ȭ�� ������ �ҷ����� �Լ�
	EGameState GetState()
	{
		return mstate;
	}
	//���¸� �ٲٴ� �Լ�
	void SetState(EGameState s);

	//Player����
	UPROPERTY(EditDefaultsOnly, Category = "PlayerClass")
	TSubclassOf<class APlayerCPP> PlayerFactory;


private:
	//���º���
	//->BP�� �����Ű�� �ʹ� ������ Private�̶� �ȉ�
	//->meta =(AllowPrivateAccess = ture)�� ���� Private�̿��� ���Ⱑ��(����Ƽ ������������ʵ�)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State", meta = (AllowPrivateAccess = ture))
	EGameState mstate = EGameState::Ready;
	//�ʿ�Ӽ� : źâũ��, źâ(������ƮǮ), �Ѿ˰���
	UPROPERTY(EditDefaultsOnly, Category = "Bullet", meta = (AllowPrivateAccess = ture))
	int bulletPoolSize = 20;

	UPROPERTY(VisibleAnywhere, Category = "Bullet", meta = (AllowPrivateAccess = ture))
	TArray<ABulletCPP*>	bulletPool;

	//����
	UPROPERTY(EditDefaultsOnly, Category = "BulletClass", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class ABulletCPP> bulletFactory;

	//State Ready�� �ʿ��� �Ӽ� : �����ð�, ����ð�
	UPROPERTY(EditAnywhere, Category = "State", meta = (AllowPrivateAccess = ture))
	float readyDelyTime = 2;
	UPROPERTY()
	float curruntTime = 0;
	//--------------------------------------------------------------------------
	//Ready Widjet BP ���� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> readyUIFactory;
	//Ready Ui�� ��Ȱ�� �ϱ����� �Ӽ����� ����� ���
	UPROPERTY()
	class UUserWidget* readyUI;

	//Start Widjet BP ���� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> startUIFactory;
	//Start Ui�� ��Ȱ�� �ϱ����� �Ӽ����� ����� ���
	UPROPERTY()
	class UUserWidget* startUI;

	//GameOver Ui�� ��Ȱ�� �ϱ����� �Ӽ����� ����� ���
	UPROPERTY()
	class UUserWidget* gameOverUI;
	//GameOver Widjet BP ���� ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> gameOverUIFactory;

	//��������
	int32 curScore = 0;
	//�ְ�����
	int32 topScore = 0;

	//User Widget -> Score UI
	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = ture))
	TSubclassOf<class UUserWidget> scoreUIFactory;

	//ScoreUi ���忡�� ������� scoreUi�� ����� ����
	UPROPERTY()
	class UScoreCPP* scoreUI;

	//SaveGame �ν��Ͻ��� ������ ���
	UPROPERTY()
	class USaveData* saveData;
	
public:
	// ���������� ���� �� ���� �Լ�
	void SetCurrentScore(int32 point);
	// ���������� �ҷ��� �� ���� �Լ�
	int32 GetCurrentScore();
};
