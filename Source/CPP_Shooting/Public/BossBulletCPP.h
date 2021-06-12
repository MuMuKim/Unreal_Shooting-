// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossBulletCPP.generated.h"

UCLASS()
class CPP_SHOOTING_API ABossBulletCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossBulletCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	//��ü
	UPROPERTY(EditAnywhere,Category = "Component")
	class UBoxComponent* boxComp;
	//�ܰ�
	UPROPERTY(EditAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;
	//�Ѿ˼ӵ�
	float speed = 1000;
	//����
	FVector dir;
	//Ÿ��
	UPROPERTY()
	class AActor* target;
};