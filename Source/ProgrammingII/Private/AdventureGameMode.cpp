#include "AdventureGameMode.h"
#include "Kismet/GameplayStatics.h"

AAdventureGameMode::AAdventureGameMode()
{
	// Make sure wave 0 can be spawned
	CurrentWave = -1;

	// Don't let next wave cycle automatically in adventure mode
	bWillAutomaticallyGoToNextWave = false;
}

void AAdventureGameMode::PickupSpecialItem()
{
	SpecialItemsQuantity++;

	// If there are many special items, delete the gate
	if (SpecialItemsQuantity >= 3)
	{
		TArray<AActor*> Gates;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Gate"), Gates);

		for (int i = 0; i < Gates.Num(); i++)
		{
			Gates[i]->Destroy();
		}
	}
}

void AAdventureGameMode::TriggerWave(int Wave)
{
	CurrentWave = Wave;

	SpawnWave();
}
