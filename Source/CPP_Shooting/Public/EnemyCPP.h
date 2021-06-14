// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "CoreMinimal.h"
#include "CPP_Shooting.h"
#include "PlayerCPP.h"
#include "GameFramework/Actor.h"
#include "EnemyCPP.generated.h"

UCLASS()
class CPP_SHOOTING_API AEnemyCPP : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* meshComp;
	//EnemyComponent Ãß°¡
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	class UEnemyMove* enemyMove;

public:	
	// Sets default values for this actor's properties
	AEnemyCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
