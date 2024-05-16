// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/HarkerAnimInstance.h"
#include "Characters/Harker.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "KismetAnimationLibrary.h"

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
		GroundSpeed     = UKismetMathLibrary::VSizeXY(HarkerCharacterMovement->Velocity);
		IsFalling       = HarkerCharacterMovement->IsFalling();
		IsStraphing     = HarkerCharacter->isZoomingIn;
		IsMovingForward = GroundSpeed > 0.0f && UKismetAnimationLibrary::CalculateDirection(HarkerCharacterMovement->Velocity, HarkerCharacter->GetActorRotation()) == 0.0f;
		IsMovingRight   = UKismetAnimationLibrary::CalculateDirection(HarkerCharacterMovement->Velocity, HarkerCharacter->GetActorRotation()) > 0.0f;
		CharacterState  = HarkerCharacter->GetCharacterState();
	}
}
