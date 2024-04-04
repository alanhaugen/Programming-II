// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UBoxComponent;
class AHarker;

UCLASS()
class PROGRAMMINGII_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Collision mesh for item
	UBoxComponent* CollisionMesh;

	UFUNCTION()
	virtual void OnSpehereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSpehereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	AHarker* Player;

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

	UPROPERTY(EditAnywhere, Category = "Item Parameters")
	float AmmunitionAmount = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Item Parameters")
	int AmmunitionType = 0;
};
