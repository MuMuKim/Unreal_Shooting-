// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "CPP_Shooting.h"
#include "PlayerCPP.h"
#include "GameFramework/Actor.h"
#include "EnemyCPP.generated.h"

UCLASS()
class CPP_SHOOTING_API AEnemyCPP : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;
	//EnemyComponent �߰�
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UEnemyMove* enemyMove;

	//����ȿ��
	UPROPERTY(EditDefaultsOnly,Category="Setting")
	class UParticleSystem* explosionFactory;
	//����ȿ�� Sound
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* explosionSound;
public:	
	// Sets default values for this actor's properties
	AEnemyCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//�浹 �̺�Ʈ ó�� �Լ�
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable, Category = "Code") //BP���� �˻��Ҽ��ְ� ���ش�
	void OnCollisionEnter(AActor* OtherActor);

	UFUNCTION() //�Լ��� U��� , �������� U������Ƽ
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
