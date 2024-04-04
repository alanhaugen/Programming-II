// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoint.h"
#include "Harker.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACheckPoint::Load()
{
	if (player)
	{
		player->SetActorLocation(GetActorLocation());
		player->SetActorRotation(GetActorRotation());

		player->AmmunitionNormal = AmmunitionNormal;
		player->AmmunitionFlame  = AmmunitionFlame;
		player->AmmunitionHoly   = AmmunitionHoly;
	}
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

