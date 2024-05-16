// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalGameMode.h"
#include "GameFramework/GameModeBase.h"
#include "AdventureGameMode.generated.h"

UCLASS()
class PROGRAMMINGII_API AAdventureGameMode : public ASurvivalGameMode
{
	GENERATED_BODY()
	
public:
	AAdventureGameMode();
	void TriggerWave(int Wave);
	void PickupSpecialItem();

private:
	int SpecialItemsQuantity = 0;
	int AmountOfSpecialItemsToOpenGates = 3;
};
