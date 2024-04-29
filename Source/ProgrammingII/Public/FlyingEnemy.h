// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "FlyingEnemy.generated.h"


class AHarker;

UCLASS()
class PROGRAMMINGII_API AFlyingEnemy : public AEnemy
{
	GENERATED_BODY()

public:
	AFlyingEnemy();

	virtual void Tick(float DeltaTime) override;
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float EnemySpeed = 300.0f;


private:
	AHarker* Player;

};
