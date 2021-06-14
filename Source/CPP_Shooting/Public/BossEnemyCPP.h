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
	//몸체(충돌체)
	UPROPERTY(EditAnywhere,Category = "Component")
	class UBoxComponent* boxComp;
	//외관
	UPROPERTY(EditAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;
	//총구위치
	UPROPERTY(EditAnywhere, Category = "Component")
	class UArrowComponent* firePosition;

	//총알공장
	UPROPERTY(EditDefaultsOnly, Category = "BulletFactory")
	TSubclassOf<class ABossBulletCPP> bulletFactory;

	//쉴드공장
	UPROPERTY(EditDefaultsOnly, Category = "ShieldFactory")
	TSubclassOf<class ABossShieldCPP> shieldFactory;

	//나선공격 공장
	UPROPERTY(EditDefaultsOnly, Category = "HelixFactory")
	TSubclassOf<class ABossHelixCPP> helixFactory;

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
	
};
