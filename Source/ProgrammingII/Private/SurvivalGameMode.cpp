#include "SurvivalGameMode.h"
#include "EnemySpawner.h"

void ASurvivalGameMode::CheckIfLastEnemy()
{
	UE_LOG(LogTemp, Warning, TEXT("current wave: %i"), CurrentWave);
	// Check if all enemies have been cleared
	if (EnemyQuantity == 0)
	{
		// Spawn a new wave
		for (int i = 0; i < Spawners.Num(); i++)
		{
			Spawners[i]->Spawn(CurrentWave);
		}

		CurrentWave++;
		EnemyQuantityForCurrentWave = EnemyQuantity;
	}
}
