// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BossShield.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_SHOOTING_API UBossShield : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBossShield();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//�Ѿ˰���
	UPROPERTY(EditDefaultsOnly, Category = "BulletFactory")
		TSubclassOf<class ABossBulletCPP> bulletFactory;

	//���߰���
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
		class UParticleSystem* expolsionFactory;

	//���߻���
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
		class USoundBase* expolsionSound;
private:
	//����ð�
	float currentTime = 0;
	//����ð�
	float createTime = 5;
	//���� Ƚ��
	int32 point = 0;

	//�� ������Ʈ�� �����ϰ� �ִ� ���� ��ü
	UPROPERTY()
	class ABossEnemyCPP* me;

	//-------
	//�ӵ�
	float theta;
	//����
	FVector retVector;
	//boss
	UPROPERTY()
	class ABossEnemyCPP* boss;
	//���� ������
	float helix = 150;
};
