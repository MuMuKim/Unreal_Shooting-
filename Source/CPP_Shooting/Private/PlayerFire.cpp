// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFire.h"
#include "CPP_ShootingGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include <Components/InputComponent.h>
#include <Components/ArrowComponent.h>

// Sets default values for this component's properties
UPlayerFire::UPlayerFire()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerFire::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<APlayerCPP>(GetOwner());
}


// Called every frame
void UPlayerFire::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerFire::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Fire 버튼 입력 바인딩 처리
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &UPlayerFire::Fire);
}

void UPlayerFire::Fire()
{
	// GameModeBase의 GetBullet을 이용하여 총알을 가져오기
	//GmaeMode를 가져온다 : 월드에서 가져온 게임모드를 Cast시켜서 변수에 넣어준다.
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	// GameMode의 State가 Playing이 아니라면 아래 코드는 실행되지 않도록 하고 싶다.
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}
	//만약 게임모드가 있다면
	if (gameMode)
	{
		//gameMode의 GetBullet함수에 리턴값인 bullet을 받아와 bullet변수로 받아준다.
		auto bullet = gameMode->GetBullet(); // 1발
		//방어코드
		if (bullet == nullptr)
		{
			return;
		}
		//두번째 총알을 가져올때 탄창에 더이상 총알이 없다면
		//발사할 수 없기 때문에 첫번째 가져온 총알은 다시 탄창에 반납한다
		auto bullet2 = gameMode->GetBullet(); // 2발
		if (bullet2 == nullptr)
		{
			gameMode->AddBullet(bullet);
			return;
		}

		//첫번째 총알을 활성화 시켜준다
		gameMode->SetbulletActive(bullet, true);
		//첫번째 총알을 FirePosition의 Location값에서 +60해 배치시킨다
		bullet->SetActorLocation(me->firePosition->GetComponentLocation() + FVector(0, 60, 0));
		bullet->SetActorRelativeRotation(me->firePosition->GetComponentRotation());

		//두번째 총알을 활성화 시켜준다
		gameMode->SetbulletActive(bullet2, true);
		//두번째 총알을 FirePosition의 Location값에서 -60해 배치시킨다
		bullet2->SetActorLocation(me->firePosition->GetComponentLocation() + FVector(0, -60, 0));
		bullet2->SetActorRelativeRotation(me->firePosition->GetComponentRotation());
	}
	//총알 발사 Sound 재생
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);
}

