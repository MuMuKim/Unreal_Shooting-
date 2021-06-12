// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCPP.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Components/ArrowComponent.h>
#include <Kismet/GameplayStatics.h>
#include "CPP_ShootingGameModeBase.h"
#include "PlayerMove.h"

// Sets default values
APlayerCPP::APlayerCPP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// BoxComponent �߰��ϱ�
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	// BoxComponunt�� ��Ʈ������Ʈ�� ����
	RootComponent = boxComp;

	// StaticMeshComponent �߰��ϱ�
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//��Ʈ�� �ڽ����� ����ϱ�
	meshComp->SetupAttachment(boxComp);
	//��Ʈ�� �浹ü�� �ֱ⋚���� �ڽ��� meshComp�� Collision�� ���ش�.
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Arrow������Ʈ �߰�
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	//��Ʈ�� �ڽ����� ����ϱ�
	firePosition->SetupAttachment(boxComp);

	//StaticMesh�� �������� �ε��ؼ� �Ҵ��ϱ�
	ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	//������ ���������� �ε��ߴٸ� True�� ����
	if (TempMesh.Succeeded())
	{
		// �о�帰 �����͸� �Ҵ�
		meshComp->SetStaticMesh(TempMesh.Object);
	}

	//����(Material) �������� �ε��ؼ� �Ҵ��ϱ�
	ConstructorHelpers::FObjectFinder<UMaterial>TempMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	//������ ���������� �ε��ߴٸ� True�� ����
	if (TempMat.Succeeded())
	{
		// �о�帰 �����͸� �Ҵ�
		meshComp->SetMaterial(0,TempMat.Object);
	}

	//PlayerMove ������Ʈ �Ҵ�
	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT ("PlayeMove"));

	//playerFire ������Ʈ �Ҵ�
	playerFire = CreateDefaultSubobject<UPlayerFire>(TEXT("PlayerFire"));
}

// Called when the game starts or when spawned
void APlayerCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
//����ڰ� �����س��� �Է� ���� ó���� �Լ��� �����ִ� ����
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//PlayerMove ������Ʈ���� ����
	playerMove->SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerFire ������Ʈ���� ����
	playerFire->SetupPlayerInputComponent(PlayerInputComponent);

}

//�Ѿ� �߻� ó��
void APlayerCPP::Fire()
{
	//�Ѿ��� �Ѿ˰��忡�� ������
 
	//���鶧 ���ڸ��� �ٸ� �༮�� �ִ��� ����������� ���� ex.�����ڸ��� ���� �ִٸ� ������ �ȵ�.
	//FActorSpawnParameters Param;
	//Collision�� �ִ��� ����
	//Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//GetWord�� ��������� ������1
	//GetWorld()->SpawnActor<ABulletCPP>(bulletFactory,
	//	firePosition->GetComponentLocation(),
	//	firePosition->GetComponentRotation(), Param);
	//-------------------------------------------------------------------------------------------
	 
	//GameModeBase�� GetBullet�� �̿��Ͽ� �Ѿ��� ��������
	//GmaeMode�� �����´� : ���忡�� ������ ���Ӹ�带 Cast���Ѽ� ������ �־��ش�.

	//auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	//// GameMode�� State�� Playing�� �ƴ϶�� �Ʒ� �ڵ�� ������� �ʵ��� �ϰ� �ʹ�.
	//if (gameMode->GetState() != EGameState::Playing)
	//{
	//	return;
	//}
	////���� ���Ӹ�尡 �ִٸ�
	//if (gameMode)
	//{
	//	//gameMode�� GetBullet�Լ��� ���ϰ��� bullet�� �޾ƿ� bullet������ �޾��ش�.
	//	auto bullet = gameMode->GetBullet(); // 1��
	//	//����ڵ�
	//	if (bullet == nullptr)
	//	{
	//		return;
	//	}
	//	//�ι�° �Ѿ��� �����ö� źâ�� ���̻� �Ѿ��� ���ٸ�
	//	//�߻��� �� ���� ������ ù��° ������ �Ѿ��� �ٽ� źâ�� �ݳ��Ѵ�
	//	auto bullet2 = gameMode->GetBullet(); // 2��
	//	if (bullet2 == nullptr)
	//	{
	//		gameMode->AddBullet(bullet);
	//		return;
	//	}
	//	
	//	//ù��° �Ѿ��� Ȱ��ȭ �����ش�
	//	gameMode->SetbulletActive(bullet, true);
	//	//ù��° �Ѿ��� FirePosition�� Location������ +60�� ��ġ��Ų��
	//	bullet->SetActorLocation(firePosition->GetComponentLocation() + FVector(0, 60, 0));
	//	bullet->SetActorRelativeRotation(firePosition->GetComponentRotation());

	//	//�ι�° �Ѿ��� Ȱ��ȭ �����ش�
	//	gameMode->SetbulletActive(bullet2, true);
	//	//�ι�° �Ѿ��� FirePosition�� Location������ -60�� ��ġ��Ų��
	//	bullet2->SetActorLocation(firePosition->GetComponentLocation()+FVector(0,-60,0));
	//	bullet2->SetActorRelativeRotation(firePosition->GetComponentRotation());
	//}
	////�Ѿ� �߻� Sound ���
	//UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);

}



