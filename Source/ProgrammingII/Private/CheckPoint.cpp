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
	
	if (GetWorld())
	{
		Player = Cast<AHarker>(GetWorld()->GetFirstPlayerController()->GetPawn());
		Player->CheckPoints.Add(this);
		Player->CurrentCheckPoint = this;
	}
}

void ACheckPoint::Load()
{
	if (Player)
	{
		Player->SetActorLocation(GetActorLocation());
		Player->SetActorRotation(GetActorRotation());

		Player->AmmunitionNormal = AmmunitionNormal;
		Player->AmmunitionFlame  = AmmunitionFlame;
		Player->AmmunitionHoly   = AmmunitionHoly;

		Player->ResetStates();
	}
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

