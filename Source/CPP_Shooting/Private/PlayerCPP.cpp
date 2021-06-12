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

	// BoxComponent 추가하기
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	// BoxComponunt를 루트컴포넌트로 설정
	RootComponent = boxComp;

	// StaticMeshComponent 추가하기
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	//루트의 자식으로 등록하기
	meshComp->SetupAttachment(boxComp);
	//루트의 충돌체가 있기떄문에 자식인 meshComp는 Collision을 꺼준다.
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Arrow컴포넌트 추가
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	//루트의 자식으로 등록하기
	firePosition->SetupAttachment(boxComp);

	//StaticMesh를 동적으로 로드해서 할당하기
	ConstructorHelpers::FObjectFinder<UStaticMesh>TempMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	//에셋을 성공적으로 로드했다면 True를 리턴
	if (TempMesh.Succeeded())
	{
		// 읽어드린 데이터를 할당
		meshComp->SetStaticMesh(TempMesh.Object);
	}

	//재질(Material) 동적으로 로드해서 할당하기
	ConstructorHelpers::FObjectFinder<UMaterial>TempMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	//에셋을 성공적으로 로드했다면 True를 리턴
	if (TempMat.Succeeded())
	{
		// 읽어드린 데이터를 할당
		meshComp->SetMaterial(0,TempMat.Object);
	}

	//PlayerMove 컴포넌트 할당
	playerMove = CreateDefaultSubobject<UPlayerMove>(TEXT ("PlayeMove"));

	//playerFire 컴포넌트 할당
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
//사용자가 정의해놓은 입력 값과 처리할 함수를 묶어주는 역할
void APlayerCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//PlayerMove 컴포넌트에서 실행
	playerMove->SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerFire 컴포넌트에서 실행
	playerFire->SetupPlayerInputComponent(PlayerInputComponent);

}

//총알 발사 처리
void APlayerCPP::Fire()
{
	//총알을 총알공장에서 만들자
 
	//만들때 그자리에 다른 녀석이 있더라도 만들어지도록 설정 ex.생성자리에 무언가 있다면 생성이 안됨.
	//FActorSpawnParameters Param;
	//Collision이 있더라도 생성
	//Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//GetWord는 가상공간을 관리함1
	//GetWorld()->SpawnActor<ABulletCPP>(bulletFactory,
	//	firePosition->GetComponentLocation(),
	//	firePosition->GetComponentRotation(), Param);
	//-------------------------------------------------------------------------------------------
	 
	//GameModeBase의 GetBullet을 이용하여 총알을 가져오기
	//GmaeMode를 가져온다 : 월드에서 가져온 게임모드를 Cast시켜서 변수에 넣어준다.

	//auto gameMode = Cast<ACPP_ShootingGameModeBase>(GetWorld()->GetAuthGameMode());
	//// GameMode의 State가 Playing이 아니라면 아래 코드는 실행되지 않도록 하고 싶다.
	//if (gameMode->GetState() != EGameState::Playing)
	//{
	//	return;
	//}
	////만약 게임모드가 있다면
	//if (gameMode)
	//{
	//	//gameMode의 GetBullet함수에 리턴값인 bullet을 받아와 bullet변수로 받아준다.
	//	auto bullet = gameMode->GetBullet(); // 1발
	//	//방어코드
	//	if (bullet == nullptr)
	//	{
	//		return;
	//	}
	//	//두번째 총알을 가져올때 탄창에 더이상 총알이 없다면
	//	//발사할 수 없기 때문에 첫번째 가져온 총알은 다시 탄창에 반납한다
	//	auto bullet2 = gameMode->GetBullet(); // 2발
	//	if (bullet2 == nullptr)
	//	{
	//		gameMode->AddBullet(bullet);
	//		return;
	//	}
	//	
	//	//첫번째 총알을 활성화 시켜준다
	//	gameMode->SetbulletActive(bullet, true);
	//	//첫번째 총알을 FirePosition의 Location값에서 +60해 배치시킨다
	//	bullet->SetActorLocation(firePosition->GetComponentLocation() + FVector(0, 60, 0));
	//	bullet->SetActorRelativeRotation(firePosition->GetComponentRotation());

	//	//두번째 총알을 활성화 시켜준다
	//	gameMode->SetbulletActive(bullet2, true);
	//	//두번째 총알을 FirePosition의 Location값에서 -60해 배치시킨다
	//	bullet2->SetActorLocation(firePosition->GetComponentLocation()+FVector(0,-60,0));
	//	bullet2->SetActorRelativeRotation(firePosition->GetComponentRotation());
	//}
	////총알 발사 Sound 재생
	//UGameplayStatics::PlaySound2D(GetWorld(), bulletSound);

}



