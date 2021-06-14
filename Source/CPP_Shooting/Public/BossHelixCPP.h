// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossHelixCPP.generated.h"

UCLASS()
class CPP_SHOOTING_API ABossHelixCPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABossHelixCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	//몸체
	UPROPERTY(EditAnywhere,Category = "Component")
	class UBoxComponent* boxComp;
	//외관
	UPROPERTY(EditAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;
	//총알속도
	float speed = 1000;
	//방향
	FVector dir;
	//타겟
	UPROPERTY()
	class AActor* target;

	//------ 
	//속도
	float theta;
	//백터
	FVector retVector;
	//boss
	UPROPERTY()
	class ABossEnemyCPP* boss;
	//나선 반지름
	float helix = 150;
};
