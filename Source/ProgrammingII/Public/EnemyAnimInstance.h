// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROGRAMMINGII_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BluePrintReadOnly, Category = Movement)
	class AEnemy* EnemyCharacter;

	UPROPERTY(BluePrintReadOnly, Category = Movement)
	class UCharacterMovementComponent* EnemyCharacterMovement;

	UPROPERTY(BluePrintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(BluePrintReadOnly, Category = Movement)
	bool IsFalling;

	UPROPERTY(BluePrintReadOnly, Category = Movement)
	bool IsDead;
};
