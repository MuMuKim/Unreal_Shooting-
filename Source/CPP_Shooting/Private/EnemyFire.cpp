// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFire.h"
#include "EnemyCPP.h"
#include "EnemyBulletCPP.h"

// Sets default values for this component's properties
UEnemyFire::UEnemyFire()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyFire::BeginPlay()
{
	Super::BeginPlay();

	me = Cast<AEnemyCPP>(GetOwner());

	//태어날 시 총알생성
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AEnemyBulletCPP>(bulletFactory, me->GetActorTransform(), param);
	
}


// Called every frame
void UEnemyFire::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

