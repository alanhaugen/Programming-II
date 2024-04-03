// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	RootComponent = BulletMesh;

	GuntipOffset = FVector(100.0f, 0.0f, 10.0f);

	SetActorLocation(GetActorLocation() + GuntipOffset);
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + (this->GetActorForwardVector() * DeltaTime * MovementSpeed));

}



