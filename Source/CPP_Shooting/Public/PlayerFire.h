// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Sound/SoundBase.h>
#include "PlayerCPP.h"
#include "PlayerFire.generated.h"

// meta = 블루프린트안에 AddComponent할때 찾을 수 있음
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_SHOOTING_API UPlayerFire : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerFire();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//사용자 입력처리 담당할 함수 (콜백: Callback)
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	//공장
	//UPROPERTY(EditDefaultsOnly, Category = "BulletClass")
	//TSubclassOf<class ABulletCPP> bulletFactory;
	//총알 발사 처리 함수
	void Fire();
	//총알 발사 Sound
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	class USoundBase* bulletSound;	

	//이 컴포넌트를 소유하고 있는 액터 객체
	UPROPERTY()
	class APlayerCPP* me;
};
