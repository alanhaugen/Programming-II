#include "Triggers/EnemySpawner.h"
#include <Math/UnrealMathUtility.h>
#include <Kismet/GameplayStatics.h>
#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <NavigationSystem.h>
#include "GameModes/SurvivalGameMode.h"
#include "Characters/Harker.h"
#include "Characters/Enemy.h"

AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		Player = Cast<AHarker>(GetWorld()->GetFirstPlayerController()->GetPawn());
		SurvivalMode = Cast<ASurvivalGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

		if (SurvivalMode)
		{
			SurvivalMode->Spawners.Add(this);
		}
	}
}

void AEnemySpawner::Spawn(int Wave)
{
	// Escape if waves array is empty or out of bounds
	if (Waves.IsEmpty())
	{
		return;
	}

	// If the next wave does not exist, create a new wave based on the last wave
	if (Wave == Waves.Num())
	{
		Waves.Add(Waves[Waves.Num() - 1] * 2);
	}
	// Espace if out of bounds (greater than one out)
	else if (Wave >= Waves.Num())
	{
		return;
	}

	// Spawn parameters (always spawn, adjust the spawn location)
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Spawn the amount of enemies corresponding to the setup for the current wave
	for (int i = 0; i < Waves[Wave]; i++)
	{
		FVector Location;
		AActor* SpawnedActor = nullptr;
		
		// Thanks to https://gist.github.com/dacanizares/5db9c59281a9c9049bf819acce7e29bc
		if (NavSys->K2_GetRandomReachablePointInRadius(GetWorld(), GetActorLocation(), Location, SpawnRadius))
		{
			SpawnedActor = GetWorld()->SpawnActor<AActor>(EnemyClass, Location, FRotator::ZeroRotator, ActorSpawnParams);
		}

		// Fallback to a simpler way of spawning if the previous method fails
		if (SpawnedActor == nullptr)
		{
			GetWorld()->SpawnActor<AActor>(EnemyClass, GetActorLocation(), FRotator::ZeroRotator);
		}
	}
}

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

	if (SurvivalMode == nullptr)
	{
		RunningTime += DeltaTime;

		SpawnTime = 3.f;

		if (RunningTime > SpawnTime) 
		{
			RunningTime = 0.0f;

			GetWorld()->SpawnActor<AActor>(EnemyClass, GetActorLocation(), FRotator::ZeroRotator);
		}
	}
}

