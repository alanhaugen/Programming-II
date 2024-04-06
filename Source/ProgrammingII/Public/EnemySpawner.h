// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "Math/UnrealMathUtility.h"
#include "EnemySpawner.generated.h"

class AHarker;

UCLASS()
class PROGRAMMINGII_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float RunningTime = 0.f;

	UPROPERTY(EditAnywhere, Category = "SpawnTimer")
	float SpawnTime;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<class AEnemy> EnemyClass;

	AHarker* Player;
};
