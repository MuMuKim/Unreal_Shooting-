// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Sound/SoundBase.h>
#include "PlayerCPP.h"
#include "PlayerFire.generated.h"

// meta = �������Ʈ�ȿ� AddComponent�Ҷ� ã�� �� ����
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_SHOOTING_API UPlayerFire : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//����� �Է�ó�� ����� �Լ� (�ݹ�: Callback)
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	//����
	//UPROPERTY(EditDefaultsOnly, Category = "BulletClass")
	//TSubclassOf<class ABulletCPP> bulletFactory;
	//�Ѿ� �߻� ó�� �Լ�
	void Fire();
	//�Ѿ� �߻� Sound
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* bulletSound;	

	//�� ������Ʈ�� �����ϰ� �ִ� ���� ��ü
	UPROPERTY()
	class APlayerCPP* me;
};
