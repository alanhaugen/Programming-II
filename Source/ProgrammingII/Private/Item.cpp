// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include "Harker.h"
#include <Components/BoxComponent.h>

AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		Player = Cast<AHarker>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}

	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSpehereOverlap);
	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSpehereEndOverlap);
}

void AItem::OnSpehereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Player->AmmunitionNormal += 10;
	Destroy();
}

void AItem::OnSpehereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Movement rate in units cm/s
	RunningTime += DeltaTime;

	// MovmentRate * DeltaTime (cm/s) * (c/frame) = (cm/frame)
	AddActorWorldOffset(FVector(0.0f, 0.0f, Amplitude * FMath::Sin(RunningTime * TimeConstant)));
	SetActorRotation(GetActorRotation() + (FRotator(0.0f, 1.0f, 0.0f) * RotationSpeed * DeltaTime));
}

