#include "AdventureGameMode.h"

AAdventureGameMode::AAdventureGameMode()
{
	// Make sure wave 0 can be spawned
	CurrentWave = -1;

	// Don't let next wave cycle automatically in adventure mode
	bWillAutomaticallyGoToNextWave = false;
}

void AAdventureGameMode::TriggerWave(int Wave)
{
	CurrentWave = Wave;

	SpawnWave();
}
