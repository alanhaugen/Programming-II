// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBarComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMINGII_API UHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	void SetHealthPercent(float Percent);

private:
	UPROPERTY() // UPROPERTY() will make HealthBar start off as a nullptr
	class UHealthBar* HealthBarWidget;
};
