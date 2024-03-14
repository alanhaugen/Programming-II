// Fill out your copyright notice in the Description page of Project Settings.

#include "Harker.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

// Sets default values
AHarker::AHarker()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// HarkerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HarkerMeshComponent"));
}

// Called when the game starts or when spawned
void AHarker::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Movement rate in units cm/s
	//float MovementRate = 50.0f;

	// MovmentRate * DeltaTime (cm/s) * (s/frame) = (cm/frame)
	//SetActorLocation(GetActorLocation() + FVector(0.0f, MovementRate * DeltaTime, 0.0f));
}

// Called to bind functionality to input
void AHarker::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHarker::Move(const FInputActionValue& Value)
{
}

void AHarker::LookAround(const FInputActionValue& Value)
{
}

