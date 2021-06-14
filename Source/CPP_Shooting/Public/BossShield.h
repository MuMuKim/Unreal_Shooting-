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


	//총알공장
	UPROPERTY(EditDefaultsOnly, Category = "BulletFactory")
		TSubclassOf<class ABossBulletCPP> bulletFactory;

	//폭발공장
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
		class UParticleSystem* expolsionFactory;

	//폭발사운드
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
		class USoundBase* expolsionSound;
private:
	//현재시간
	float currentTime = 0;
	//경과시간
	float createTime = 5;
	//맞은 횟수
	int32 point = 0;

	//이 컴포넌트를 소유하고 있는 액터 객체
	UPROPERTY()
	class ABossEnemyCPP* me;

	//-------
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
