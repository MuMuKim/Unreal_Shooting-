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
	//EnemyComponent 추가
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UEnemyMove* enemyMove;

	//폭발효과
	UPROPERTY(EditDefaultsOnly,Category="Setting")
	class UParticleSystem* explosionFactory;
	//폭발효과 Sound
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

	//충돌 이벤트 처리 함수
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable, Category = "Code") //BP에서 검색할수있게 해준다
	void OnCollisionEnter(AActor* OtherActor);

	UFUNCTION() //함수는 U펑션 , 변수들은 U프로퍼티
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
