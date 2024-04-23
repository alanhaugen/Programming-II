#include "SurvivalGameMode.h"
#include "EnemySpawner.h"
#include "Harker.h"

void ASurvivalGameMode::CheckIfLastEnemy()
{
	// Don't continue if auto cycling through waves is disabled
	if (bWillAutomaticallyGoToNextWave == false)
	{
		return;
	}

	// Get reference to player
	AHarker* Player;

	if (GetWorld())
	{
		Player = Cast<AHarker>(GetWorld()->GetFirstPlayerController()->GetPawn());

		// Don't continue without instance to player
		if (Player == nullptr)
		{
			return;
		}

		// Don't continue if player has yet to equip a weapon
		if (Player->GetCharacterState() == ECharacterState::ECS_Unequipped)
		{
			return;
		}
	}

	// Check if all enemies have been cleared
	if (EnemyQuantity == 0)
	{
		// Spawn a new wave
		SpawnWave();
		CurrentWave++;
	}
}

void ASurvivalGameMode::PickupSpecialItem()
{
}

void ASurvivalGameMode::SpawnWave()
{
	// Don't spawn if array is out of bounds
	if (CurrentWave < 0)
	{
		return;
	}

	// Spawn a new wave
	for (int i = 0; i < Spawners.Num(); i++)
	{
		Spawners[i]->Spawn(CurrentWave);
	}

	EnemyQuantityForCurrentWave = EnemyQuantity;
}
