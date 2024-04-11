// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "HUD/HealthBarComponent.h"
#include "AttributeComponent.h"
#include <Animation/AnimMontage.h>
#include <AIController.h>

AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	return 0.0f;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(1.0f);
	}
}

void AEnemy::DeathEnd()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

	AnimInstance->Montage_Pause();
}

void AEnemy::UpdateUI()
{
	if (HealthBarWidget)
	{
		HealthBarWidget->SetHealthPercent(Attributes->Health / Attributes->MaxHealth);
	}
}

void AEnemy::UpdateDeathLogic()
{
	if (IsDead == false && Attributes->Health <= 0.0f)
	{
		// Play animation montage
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		AnimInstance->Montage_Play(DeathMontage);

		const int32 Selection = FMath::RandRange(0, 3);
		FName SelectionName;

		switch (Selection)
		{
		case 0:
			SelectionName = FName("Death1");
			break;
		case 1:
			SelectionName = FName("Death2");
			break;
		case 2:
			SelectionName = FName("Death3");
			break;
		case 3:
			SelectionName = FName("Death4");
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Invalid animation"));
		}

		AnimInstance->Montage_JumpToSectionsEnd(SelectionName, DeathMontage);
		IsDead = true;
	}
}

void AEnemy::MoveToNextWaypoint()
{
	if (Waypoints.Num() == 0)
		return;

	FVector CurrentLocation = GetActorLocation();  // get the currect actor location 
	FVector TargetLocation = Waypoints[CurrentWaypointIndex]->GetActorLocation();  // get the current waypoint location // starts from index 0 

	// When we get close to the targe, then change to the next way point 
	if (FVector::Dist(TargetLocation, CurrentLocation) < 100.0f)
	{
		CurrentWaypointIndex += 1;
		if (CurrentWaypointIndex >= Waypoints.Num())
		{
			CurrentWaypointIndex = 0;
		}
	}
	else
	{
		AAIController* AIController = Cast<AAIController>(GetController());

		if (AIController)
		{
			AIController->MoveToLocation(TargetLocation);
		}
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateUI();

	UpdateDeathLogic();

	MoveToNextWaypoint();
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
