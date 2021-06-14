// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "CPP_Shooting.h"
#include "EnemyCPP.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class CPP_SHOOTING_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyManager();

	//Ÿ�̸Ӹ� �̿��� Enemy������ �Լ�
	void CreateEnemy();
	//Ÿ�̸Ӹ� ����� ���� ����ü
	UPROPERTY()
	FTimerHandle createTimer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//����ð�, �����ð�, ������
	UPROPERTY(EditAnywhere,Category = "Setting")
	float createTime = 2;
	UPROPERTY()
	float crruntTime = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Enemy")
	TSubclassOf<class AEnemyCPP> EnemyFactory;
};
