#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "Math/UnrealMathUtility.h"
#include "EnemySpawner.generated.h"

class AHarker;
class ASurvivalGameMode;
class UNavigationSystemV1;

UCLASS()
class PROGRAMMINGII_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

	virtual void Tick(float DeltaTime) override;

	float RunningTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Spawn Options")
	TArray<int> Waves;

	UPROPERTY(EditAnywhere, Category = "Spawn Options")
	TSubclassOf<class AEnemy> EnemyClass;

	UPROPERTY(EditAnywhere, Category = "Spawn Options")
	float SpawnRadius = 500.0f;

	UPROPERTY(EditAnywhere, Category = Default)
	float SpawnTime;

	UFUNCTION(BlueprintCallable)
	void Spawn(int Wave);

protected:
	virtual void BeginPlay() override;

private:
	AHarker* Player;
	ASurvivalGameMode* SurvivalMode;
	UNavigationSystemV1* NavSys;
};
