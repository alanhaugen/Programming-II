// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Ladder.generated.h"

UCLASS()
class PROGRAMMINGII_API ALadder : public AInteractable
{
	GENERATED_BODY()
	
public:
	ALadder();

	// Collision mesh for top of the ladder
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionMeshTop;

protected:
	virtual void BeginPlay() override;
};
