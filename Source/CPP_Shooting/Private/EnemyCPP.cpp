// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCPP.h"
#include <Components/BoxComponent.h> //�߰��ؾ���
#include <Components/StaticMeshComponent.h> //�߰��ؾ���
#include <Kismet/GameplayStatics.h>
#include "CPP_ShootingGameModeBase.h"
#include "PlayerCPP.h"


// Sets default values
AEnemyCPP::AEnemyCPP()
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
void AEnemyCPP::BeginPlay()
{
	Super::BeginPlay();

	//������Ʈ �浹�� ����� �̺�Ʈ �Լ��� �����ϰ� �ʹ�.
	//�ʿ��Ѱ� :ó���� �̺�Ʈ �Լ�
	//->������Ʈ �浹�� ���ؼ��� AddDynamic�Լ��� �̿��ؾ��Ѵ�
	//->AddDynamic �Լ��� ���ڷ� ��ϵǴ� �Լ��� �ݵ�� UFUNCTION ��ũ�θ� ����ؾ��Ѵ�.
	//boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCPP::OnTriggerEnter);

	//TArray�� �𸮾� �迭.�����ȿ� ���� �ڷ����� �־���,�ּҸ� �޾ƾ���(���������ʱ�����)
	TArray<AActor*> objs; // Ÿ��(�÷��̾�)�� ���� �׸�
	//�����Ҵ� : �¾ �� Ÿ���� ã�� ����

	//����� Actor�� ã�Ƴֱ� (�迭�� ��ƾ���)
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCPP::StaticClass(), objs);

	//for ������ objs�˻�
	for (AActor* actor : objs) //actor��� �ӽú����� objs�� ��� �ڷḸŭ ���� �ִ´�
	{
		target = actor;
	}
	//���Ʒ��� ���� ��
	/*for (int i = 0; i < objs.Num(); i++)
	{
		target = objs[0];
	}*/

	//�Ʒ��� ����, 50%���ϸ� Ÿ�ٹ������� ����.
	//ó�� dir���� �Ʒ���������
	dir = FVector(0, 0, -1);

	//��������
	int32 ab = FMath::FRandRange(1, 100);
	
	//���� Ÿ�ٿ� ���� ����� ��� �ִٸ� 
	if (target != nullptr)
	{
		//���� Ȯ���� 50%���ϸ� Ÿ�ٹ���
		if (ab <= 50)
		{
			//dir���� Ÿ�� - me ������ Ÿ�ٹ����� ���Ѵ�
			dir = target->GetActorLocation() - GetActorLocation();
		}
	}
}

// Called every frame
void AEnemyCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//���ⱸ�ϱ�
	// Ÿ���� �ְ�, Ÿ���� ��ȿ�ϴٸ�(Ÿ���� �׾��� �� ���������� ����)
	if (target && IsValid(target))
	{
		dir; //�¾ �� ���� �״��
	}
	else
	{
		//�Ʒ���
		dir = FVector(0, 0, -1);
	}
	dir.Normalize();

	FVector v = dir * 500;

	FVector P0 = GetActorLocation();
	FVector P = P0 + v * DeltaTime;
	SetActorLocation(P,true);

}

//�ٸ� ��ü�� ������ �� ȣ��Ǵ� �̺�Ʈ �Լ�
//���װ� ������
//void AEnemyCPP::NotifyActorBeginOverlap(AActor* OtherActor)


void AEnemyCPP::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Enemy ���� �浹���� �ʰ� �ϰ� �ʹ�.
	
	//OtherActor�� AEnemy�� ����ȯ �Ѵ�. �ȵǸ� NULL�� ��ȯ.
	AEnemyCPP* enemy = Cast<AEnemyCPP>(OtherActor);
	if (enemy != nullptr)
	{
		//���࿡ enemy������ Null�� �ƴ϶�� �Ʒ��� �������� �ʴ´�
		return; //�Լ��� �������ش�
	}
	// ���Ʒ� ���� ���
	/*if (OtherActor->GetName().Contains(TEXT("Enemy")))
	{
		return;
	}*/

	//����ȿ�� ����
	//�ں��� ->���� Transform���� ex�� �ν��Ͻ��� ����� ���Ѷ�
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory,
		GetActorTransform());
	//����ȿ�� Sound
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	OtherActor->Destroy(); //���װ�
	Destroy(); //������ this����
}

void AEnemyCPP::OnCollisionEnter(AActor* OtherActor)
{
	//����ȿ�� ����
	//�ں��� ->���� Transform���� ex�� �ν��Ͻ��� ����� ���Ѷ�
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFactory,
		GetActorTransform());
	//����ȿ�� Sound
	UGameplayStatics::PlaySound2D(GetWorld(), explosionSound);

	//�ε��� Actor�� Bullet�� ��� źâ�� �ٽ� �־�����
	//bullet �����ȿ� otherActor(��������)�� BulletŸ������ ����ȯ��Ų��.
	auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	auto bullet = Cast<ABulletCPP>(OtherActor);
	if (bullet) //Bullet�� �´ٸ�
	{
		//Bullet�� ���� �ڸ��� �־��ش�
		gameMode->AddBullet(bullet);
	}
	else
	{
		//�ε����༮�� Player�� 
		auto player = Cast<APlayerCPP>(OtherActor);
		if (player)
		{
			//GameOver�� �����ϰ�ʹ�
			gameMode->SetState(EGameState::GameOver);
		}
		OtherActor->Destroy(); //���װ�
	}

	//������ �÷�����
	gameMode->SetCurrentScore(gameMode->GetCurrentScore() + 1);

	Destroy(); //������ this����
}

