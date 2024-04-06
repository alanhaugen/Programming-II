// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Math/UnrealMathUtility.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Harker.h"
#include "Enemy.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		Player = Cast<AHarker>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Don't spawn enemies before the player has found and equipped the crossbow
	if (Player)
	{
		if (Player->GetCharacterState() == ECharacterState::ECS_Unequipped)
		{
			return;
		}
	}

	RunningTime += DeltaTime;

	SpawnTime = 3.f;

	if (RunningTime > SpawnTime) 
	{
		RunningTime = 0.0f;

		GetWorld()->SpawnActor<AEnemy>(EnemyClass, GetActorLocation(), FRotator::ZeroRotator);
	}

}

