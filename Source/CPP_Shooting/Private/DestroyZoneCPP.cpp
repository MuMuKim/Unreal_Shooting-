// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyZoneCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "PlayerCPP.h"
#include "CPP_ShootingGameModeBase.h"
#include "BulletCPP.h"

// Sets default values
ADestroyZoneCPP::ADestroyZoneCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Box������Ʈ �߰��ϱ�
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollition"));
	//Box������Ʈ�� ��Ʈ������Ʈ�� ����
	RootComponent = boxComp;

	//StaticMesh������Ʈ �߰��ϱ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMesh������Ʈ�� ��Ʈ������Ʈ�� �ڽ����� ���
	meshComp->SetupAttachment(boxComp);
	//��Ʈ�� �浹ü�� �ֱ⋚���� �ڽ��� meshComp�� Collision�� ���ش�.
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ADestroyZoneCPP::BeginPlay()
{
	Super::BeginPlay();
	
	//������Ʈ �浹�� ����� �̺�Ʈ �Լ��� �����ϰ� �ʹ�.
	//�ʿ��Ѱ� :ó���� �̺�Ʈ �Լ�
	//->������Ʈ �浹�� ���ؼ��� AddDynamic�Լ��� �̿��ؾ��Ѵ�
	//->AddDynamic �Լ��� ���ڷ� ��ϵǴ� �Լ��� �ݵ�� UFUNCTION ��ũ�θ� ����ؾ��Ѵ�.
	boxComp->OnComponentHit.AddDynamic(this, &ADestroyZoneCPP::OnColliderEnter);
}

// Called every frame
void ADestroyZoneCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyZoneCPP::OnColliderEnter(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//���� ���� ����� Player�� �ƴϸ� ���δ�.
	APlayerCPP* player = Cast<APlayerCPP>(OtherActor);

	if (player != nullptr)
	{
		return;
	}

	//�ε��� Actor�� Bullet�� ��� źâ�� �ٽ� �־�����
	//bullet �����ȿ� otherActor(��������)�� BulletŸ������ ����ȯ��Ų��.
	auto bullet = Cast<ABulletCPP>(OtherActor);
	if (bullet) //Bullet�� �´ٸ�
	{
		//Bullet�� ���� �ڸ��� �־��ش�
		auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
		gameMode->AddBullet(bullet);
	}
	else
	{
		OtherActor->Destroy(); 
	}
}

