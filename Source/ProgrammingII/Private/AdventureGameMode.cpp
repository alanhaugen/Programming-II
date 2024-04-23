// Fill out your copyright notice in the Description page of Project Settings.


#include "AdventureGameMode.h"

AAdventureGameMode::AAdventureGameMode()
{
	// Make sure wave 0 can be spawned
	CurrentWave = -1;
}

void AAdventureGameMode::TriggerWave(int Wave)
{
	CurrentWave = Wave;

	SpawnWave();
}
