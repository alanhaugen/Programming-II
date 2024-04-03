// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Umbrella.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMINGII_API AUmbrella : public AItem
{
	GENERATED_BODY()
	
public:
	AUmbrella();

	// Mesh for Umbrella
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Umbrella Settings")
	class UStaticMeshComponent* UmbrellaMesh;
};
