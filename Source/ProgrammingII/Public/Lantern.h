// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Lantern.generated.h"

UCLASS()
class PROGRAMMINGII_API ALantern : public AItem
{
	GENERATED_BODY()

public:
	ALantern();

	// Mesh for Umbrella
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Settings")
	class UStaticMeshComponent* LanternMesh;
};
