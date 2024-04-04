// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckPoint.generated.h"

class AHarker;

UCLASS()
class PROGRAMMINGII_API ACheckPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPoint();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	AHarker* player;

public:	
	void Load();

	UPROPERTY(EditAnywhere)
	float AmmunitionNormal = 20.0f;

	UPROPERTY(EditAnywhere)
	float AmmunitionFlame = 10.0f;

	UPROPERTY(EditAnywhere)
	float AmmunitionHoly = 1.0f;

	UPROPERTY(EditAnywhere)
	int Wave = 0;
};
