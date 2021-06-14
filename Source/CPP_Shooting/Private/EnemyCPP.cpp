// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCPP.h"
#include <Components/BoxComponent.h> //�߰��ؾ���
#include <Components/StaticMeshComponent.h> //�߰��ؾ���
#include <Kismet/GameplayStatics.h>
#include "CPP_ShootingGameModeBase.h"
#include "PlayerCPP.h"
#include "EnemyMove.h"


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

	//EnemyMove Component �߰�
	enemyMove = CreateDefaultSubobject<UEnemyMove>(TEXT("EnemyMove"));
}

// Called when the game starts or when spawned
void AEnemyCPP::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AEnemyCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	

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

