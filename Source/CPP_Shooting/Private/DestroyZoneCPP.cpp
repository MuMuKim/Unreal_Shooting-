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
	//Box컴포넌트 추가하기
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollition"));
	//Box컴포넌트를 루트컴포넌트로 설정
	RootComponent = boxComp;

	//StaticMesh컴포넌트 추가하기
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//StaticMesh컴포넌트를 루트컴포넌트의 자식으로 등록
	meshComp->SetupAttachment(boxComp);
	//루트의 충돌체가 있기떄문에 자식인 meshComp는 Collision을 꺼준다.
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void ADestroyZoneCPP::BeginPlay()
{
	Super::BeginPlay();
	
	//컴포넌트 충돌을 담당할 이벤트 함수를 연결하고 싶다.
	//필요한것 :처리할 이벤트 함수
	//->컴포넌트 충돌을 위해서는 AddDynamic함수를 이용해야한다
	//->AddDynamic 함수의 인자로 등록되는 함수는 반드시 UFUNCTION 매크로를 사용해야한다.
	boxComp->OnComponentHit.AddDynamic(this, &ADestroyZoneCPP::OnColliderEnter);
}

// Called every frame
void ADestroyZoneCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyZoneCPP::OnColliderEnter(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//만약 닿은 대상이 Player가 아니면 죽인다.
	APlayerCPP* player = Cast<APlayerCPP>(OtherActor);

	if (player != nullptr)
	{
		return;
	}

	//부딪힌 Actor가 Bullet일 경우 탄창에 다시 넣어주자
	//bullet 변수안에 otherActor(닿은액터)를 Bullet타입으로 형변환시킨다.
	auto bullet = Cast<ABulletCPP>(OtherActor);
	if (bullet) //Bullet이 맞다면
	{
		//Bullet을 원래 자리로 넣어준다
		auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
		gameMode->AddBullet(bullet);
	}
	else
	{
		OtherActor->Destroy(); 
	}
}

