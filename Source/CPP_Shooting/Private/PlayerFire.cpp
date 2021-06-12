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
	//Fire ��ư �Է� ���ε� ó��
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &UPlayerFire::Fire);
}

void UPlayerFire::Fire()
{
	// GameModeBase�� GetBullet�� �̿��Ͽ� �Ѿ��� ��������
	//GmaeMode�� �����´� : ���忡�� ������ ���Ӹ�带 Cast���Ѽ� ������ �־��ش�.
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	// GameMode�� State�� Playing�� �ƴ϶�� �Ʒ� �ڵ�� ������� �ʵ��� �ϰ� �ʹ�.
	if (gameMode->GetState() != EGameState::Playing)
	{
		return;
	}
	//���� ���Ӹ�尡 �ִٸ�
	if (gameMode)
	{
		//gameMode�� GetBullet�Լ��� ���ϰ��� bullet�� �޾ƿ� bullet������ �޾��ش�.
		auto bullet = gameMode->GetBullet(); // 1��
		//����ڵ�
		if (bullet == nullptr)
		{
			return;
		}
		//�ι�° �Ѿ��� �����ö� źâ�� ���̻� �Ѿ��� ���ٸ�
		//�߻��� �� ���� ������ ù��° ������ �Ѿ��� �ٽ� źâ�� �ݳ��Ѵ�
		auto bullet2 = gameMode->GetBullet(); // 2��
		if (bullet2 == nullptr)
		{
			gameMode->AddBullet(bullet);
			return;
		}

		//ù��° �Ѿ��� Ȱ��ȭ �����ش�
		gameMode->SetbulletActive(bullet, true);
		//ù��° �Ѿ��� FirePosition�� Location������ +60�� ��ġ��Ų��
		bullet->SetActorLocation(me->firePosition->GetComponentLocation() + FVector(0, 60, 0));
		bullet->SetActorRelativeRotation(me->firePosition->GetComponentRotation());

		//�ι�° �Ѿ��� Ȱ��ȭ �����ش�
		gameMode->SetbulletActive(bullet2, true);
		//�ι�° �Ѿ��� FirePosition�� Location������ -60�� ��ġ��Ų��
		bullet2->SetActorLocation(me->firePosition->GetComponentLocation() + FVector(0, -60, 0));
		bullet2->SetActorRelativeRotation(me->firePosition->GetComponentRotation());
	}
	//�Ѿ� �߻� Sound ���
	UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);
}

