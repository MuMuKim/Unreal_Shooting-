// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossEnemyCPP.generated.h"

UCLASS()
class CPP_SHOOTING_API ABossEnemyCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossEnemyCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnColliderEnter(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	//��ü(�浹ü)
	UPROPERTY(EditAnywhere,Category = "Component")
	class UBoxComponent* boxComp;
	//�ܰ�
	UPROPERTY(EditAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;
	//�ѱ���ġ
	UPROPERTY(EditAnywhere, Category = "Component")
	class UArrowComponent* firePosition;

	//�Ѿ˰���
	UPROPERTY(EditDefaultsOnly, Category = "BulletFactory")
	TSubclassOf<class ABossBulletCPP> bulletFactory;

	//�������
	UPROPERTY(EditDefaultsOnly, Category = "ShieldFactory")
	TSubclassOf<class ABossShieldCPP> shieldFactory;

	//�������� ����
	UPROPERTY(EditDefaultsOnly, Category = "HelixFactory")
	TSubclassOf<class ABossHelixCPP> helixFactory;

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
	
};
