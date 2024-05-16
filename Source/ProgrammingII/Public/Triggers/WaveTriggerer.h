// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveTriggerer.generated.h"

class UBoxComponent;

UCLASS()
class PROGRAMMINGII_API AWaveTriggerer : public AActor
{
	GENERATED_BODY()
	
public:	
	AWaveTriggerer();

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "Wave Trigger Parameters")
	int WaveToTrigger = 0;

	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;

private:	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;
};
