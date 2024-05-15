// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "HUD/HealthBarComponent.h"
#include "AttributeComponent.h"
#include <Animation/AnimMontage.h>
#include <AIController.h>
#include <Perception/AIPerceptionComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Components/CapsuleComponent.h>
#include <Kismet/GameplayStatics.h>
#include "AdventureGameMode.h"
#include "SurvivalGameMode.h"
#include "Harker.h"
#include "Item.h"

AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup attributes and health widget
	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));
	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());
}

// UE Take Damage method (found in AActor): https://www.unrealengine.com/en-US/blog/damage-in-ue4
float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Apply damage
	Attributes->Health -= DamageAmount;

	// Amount of damage actually applied
	return DamageAmount;
}

// Update Walk Speed is used in the AI Blueprints
void AEnemy::UpdateWalkSpeed(float NewWalkSpeed) const
{
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->MaxWalkSpeed = NewWalkSpeed;
	}
}

void AEnemy::CancelWaypoints()
{
	Waypoints.Empty();
}

void AEnemy::SpawnRandomPickup()
{
	// ChanceOfDroppingItem dictates chance of spawning an item (somewhat random spawning)
	if (FMath::RandRange(0, ChanceOfDroppingItem) == 0)
	{
		// Randomly choose a pickup to spawn
		const int32 Selection = FMath::RandRange(0, 4);
		TSubclassOf<AItem> ItemToSpawn;

		switch (Selection)
		{
		case 0: // There is a bigger chance (0 & 1) that normal ammo spawns
		case 1:
			ItemToSpawn = NormalAmmoPickup;
			break;
		case 2:
			ItemToSpawn = FireAmmoPickup;
			break;
		case 3:
			ItemToSpawn = HolyAmmoPickup;
			break;
		case 4:
			ItemToSpawn = HealthPickup;
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("Invalid pickup"));
		}

		// Spawn item
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		UWorld* World = GetWorld();

		if (World && ItemToSpawn)
		{
			World->SpawnActor<AActor>(ItemToSpawn, GetActorLocation(), FRotator::ZeroRotator, ActorSpawnParams);
		}
	}
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	// Setup wealth widget (above enemy's head)
	if (HealthBarWidget)
	{
		// Initialise widget to full health
		HealthBarWidget->SetHealthPercent(1.0f);
	}

	if (GetWorld())
	{
		// Increase amount of enemies counter
		SurvivalMode = Cast<ASurvivalGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		
		if (SurvivalMode)
		{
			SurvivalMode->EnemyQuantity++;
		}

		// Get player 
		Player = Cast<AHarker>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}
}

void AEnemy::AttackEnd()
{
	IsAttacking = false;
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

		// Play a random death animation
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

		// Spawn pickup on death
		SpawnRandomPickup();

		// Keep track of number of enemies
		if (SurvivalMode)
		{
			SurvivalMode->EnemyQuantity--;

			AAdventureGameMode* AdventureMode = Cast<AAdventureGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			
			if (AdventureMode == nullptr)
			{
				// Potentially start a new wave of enemies (for survival game mode)
				SurvivalMode->CheckIfLastEnemy();
			}
		}

		// Stop processing AI on dead agent
		RemoveAIComponent();

		// Disable all enemy logic
		HealthBarWidget->SetVisibility(false);
		GetCharacterMovement()->SetActive(false);
		GetCapsuleComponent()->SetActive(false);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AEnemy::MoveToNextWaypoint()
{
	// Check if there are waypoints to travel between and if the waypoint still exists (It might have been destroyed)
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController == nullptr || Waypoints.Num() == 0 || Waypoints[CurrentWaypointIndex] == nullptr)
	{
		return;
	}

	// Choose next waypoint
	FVector CurrentLocation = GetActorLocation();  // get the currect actor location 
	FVector TargetLocation = Waypoints[CurrentWaypointIndex]->GetActorLocation();  // get the current waypoint location // starts from index 0 

	// When we get close to the targe, then change to the next way point 
	float MinimumWaypointDistance = 200.0f;
	
	if (FVector::Dist(TargetLocation, CurrentLocation) < MinimumWaypointDistance)
	{
		CurrentWaypointIndex++;

		if (CurrentWaypointIndex >= Waypoints.Num())
		{
			CurrentWaypointIndex = 0;
		}
	}
	else
	{
		AIController->MoveToLocation(TargetLocation);
	}
}

void AEnemy::Combat()
{
	// Don't attack if dead
	if (IsDead)
	{
		return;
	}

	// Get vectors for enemy location and player location
	FVector CurrentLocation = GetActorLocation();
	FVector PlayerLocation  = Player->GetActorLocation();

	// Check if enemy or player can attack melee
	float AttackDistance = 150.0f;

	if (FVector::Dist(PlayerLocation, CurrentLocation) < AttackDistance)
	{
		// Check if hit by player's umbrella (melee combat)
		if (Player->GetCharacterActionState() == EActionState::EAS_Attacking)
		{
			FDamageEvent DamageEvent;
			TakeDamage(1.0f, DamageEvent, nullptr, Player);
		}
		
		// Attack melee if possible
		if (IsAttacking == false)
		{
			// Attack has started
			IsAttacking = true;

			// Play animation montage
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

			AnimInstance->Montage_Play(AttackMontage);

			const int32 Selection = FMath::RandRange(0, 2);
			FName SelectionName;

			// Play a random attack animation
			switch (Selection)
			{
			case 0:
				SelectionName = FName("Attack1");
				break;
			case 1:
				SelectionName = FName("Attack2");
				break;
			case 2:
				SelectionName = FName("Attack3");
				break;
			default:
				UE_LOG(LogTemp, Warning, TEXT("Invalid animation"));
			}

			AnimInstance->Montage_JumpToSection(SelectionName, AttackMontage);

			// Apply damage to player
			Player->Health -= AttackDamage;
		}
	}
}

void AEnemy::RemoveAIComponent() const
{
	// Thanks to https://www.reddit.com/r/unrealengine/comments/6a8id9/question_how_do_stop_my_ai_move_to_node_from/
	AController* CurrentController = GetController();
	if (CurrentController)
	{
		// Stop movement so the death animation plays immediately
		CurrentController->StopMovement();

		// Unpossess to stop AI
		CurrentController->UnPossess();

		// Destroy the controller, since it's not part of the enemy anymore
		CurrentController->Destroy();
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateUI();

	Combat();

	UpdateDeathLogic();

	MoveToNextWaypoint();

	// Hide / Show Health Bar
	float HealthBarDistance = 2500.0f;

	if (IsDead == false && FVector::Dist(Player->GetActorLocation(), GetActorLocation()) < HealthBarDistance)
	{
		HealthBarWidget->SetVisibility(true);
	}
	else
	{
		HealthBarWidget->SetVisibility(false);
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
