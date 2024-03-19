// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HarkerAnimInstance.generated.h"

UCLASS()
class PROGRAMMINGII_API UHarkerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BluePrintReadOnly, Category = Movement)
	class AHarker* HarkerCharacter;

	UPROPERTY(BluePrintReadOnly, Category = Movement)
	class UCharacterMovementComponent* HarkerCharacterMovement;

	UPROPERTY(BluePrintReadOnly, Category = Movement)
	float GroundSpeed;
};
