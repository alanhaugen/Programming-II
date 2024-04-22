// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivalGameMode.generated.h"

class AEnemySpawner;

UCLASS()
class PROGRAMMINGII_API ASurvivalGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Track number of enemies (for survival game mode)
	UPROPERTY(BlueprintReadOnly)
	int EnemyQuantity = 0;

	// Keep track of current wave
	UPROPERTY(BlueprintReadOnly)
	int CurrentWave = 0;

	// Total number of enemies in wave
	UPROPERTY(BlueprintReadOnly)
	int EnemyQuantityForCurrentWave = 0;

	TArray<AEnemySpawner*> Spawners;

	// Call this when an enemy dies
	void CheckIfLastEnemy();

	void PickupSpecialItem();
};
