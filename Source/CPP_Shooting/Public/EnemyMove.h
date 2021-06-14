// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyMove.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_SHOOTING_API UEnemyMove : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyMove();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//폭발효과
	UPROPERTY(EditDefaultsOnly,Category="Setting")
	class UParticleSystem* explosionFactory;
	//폭발효과 Sound
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* explosionSound;

	//필요속성 : 타겟
	UPROPERTY()
	class AActor* target;
	UPROPERTY()
	FVector dir;

	//이 컴포넌트를 소유하고 있는 액터 객체
	UPROPERTY()
	class AEnemyCPP* me;

	UFUNCTION(BlueprintCallable, Category = "Code") //BP에서 검색할수있게 해준다
	void OnCollisionEnter(AActor* OtherActor);
};
