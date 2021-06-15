// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBulletCPP.generated.h"

UCLASS()
class CPP_SHOOTING_API AEnemyBulletCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBulletCPP();

	//��ü
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class USphereComponent* spComp;
	//�ܰ�
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Code")
	void OnCollisionEnter(AActor* OtherActor);

	//����ȿ��
	UPROPERTY(EditDefaultsOnly,Category="Setting")
	class UParticleSystem* explosionFactory;
	//����ȿ�� Sound
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* explosionSound;
};
