// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAnimInstance.h"
#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	EnemyCharacter = Cast<AEnemy>(TryGetPawnOwner());

	if (EnemyCharacter)
	{
		EnemyCharacterMovement = EnemyCharacter->GetCharacterMovement();
	}
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (EnemyCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(EnemyCharacterMovement->Velocity);
		IsFalling = EnemyCharacterMovement->IsFalling();
	}
}
