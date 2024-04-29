// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingEnemy.h"
#include "Harker.h"

AFlyingEnemy::AFlyingEnemy()
{
	AttackDamage = 0.1f;
}

void AFlyingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDead)
	{
		return;
	}

	FVector Direction = Player->GetActorLocation() - GetActorLocation();
	

	if (Direction.Length() > 100.0f)
	{
		Direction /= Direction.Length();
		SetActorLocation(GetActorLocation() + (Direction * EnemySpeed * DeltaTime));
	}
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
