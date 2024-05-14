// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingEnemy.h"
#include <AIController.h>
#include "Harker.h"


AFlyingEnemy::AFlyingEnemy()
{
	AttackDamage = 0.1f;
}

void AFlyingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Don't move if dead
	if (IsDead)
	{
		return;
	}

	// Special movement and attack logic for flying enemies
	// Vector from enemy to playr
	FVector Direction = Player->GetActorLocation() - GetActorLocation();
	
	// Move only if far away from player
	if (Direction.Length() > 100.0f)
	{
		// Move towards player at EnemySpeed, will also move upwards flying up to the player
		Direction /= Direction.Length();
		SetActorLocation(GetActorLocation() + (Direction * EnemySpeed * DeltaTime));
	}
	// Attack the player when close
	else
	{
		Player->Health -= AttackDamage;
	}
}

void AFlyingEnemy::BeginPlay()
{
	AEnemy::BeginPlay();

	if (GetWorld())
	{
		Player = Cast<AHarker>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}
}
