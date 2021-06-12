// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletCPP.h"
#include <Components/BoxComponent.h> //�߰��ؾ���
#include <Components/StaticMeshComponent.h> //�߰��ؾ���

// Sets default values
ABulletCPP::ABulletCPP()
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
void ABulletCPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector v = FVector(0, 0, 1);//����
	v.Normalize(); //����ȭ
	v *= 1000; //v�� 500�� ����(�ӵ�)
	FVector P0 = GetActorLocation(); //������ġ�� ������
	FVector P = P0 + v * DeltaTime; // P = P0 + vt
	SetActorLocation(P,true);// ��ġ���� -> ��ġ�̵�

}

