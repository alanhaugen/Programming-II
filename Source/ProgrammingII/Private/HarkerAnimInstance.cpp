// Fill out your copyright notice in the Description page of Project Settings.


#include "HarkerAnimInstance.h"
#include "Harker.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UHarkerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	HarkerCharacter = Cast<AHarker>(TryGetPawnOwner());

	if (HarkerCharacter)
	{
		HarkerCharacterMovement = HarkerCharacter->GetCharacterMovement();
	}
}

void UHarkerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (HarkerCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(HarkerCharacterMovement->Velocity);
		IsFalling = HarkerCharacterMovement->IsFalling();
		CharacterState = HarkerCharacter->GetCharacterState();
	}
}
