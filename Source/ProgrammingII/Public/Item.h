// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class PROGRAMMINGII_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Blueprint visible
	UPROPERTY(VisibleAnywhere, Category = "Item Parameters")
	float RunningTime;

	UPROPERTY(EditAnywhere, Category = "Item Parameters")
	float Amplitude = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Item Parameters")
	float TimeConstant = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Item Parameters")
	float RotationSpeed = 50.0f;
};
