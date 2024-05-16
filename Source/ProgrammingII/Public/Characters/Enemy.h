// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class UAttributeComponent;
class UAnimMontage;
class UHealthBarComponent;
class ASurvivalGameMode;
class AHarker;
class AItem;

UCLASS()
class PROGRAMMINGII_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Enemy state
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool IsAttacking = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool IsDead = false;

	// How much damage this enemy deals on attack
	UPROPERTY(EditAnywhere)
	float AttackDamage = 10.0f;

	// UE Take Damage method: https://www.unrealengine.com/en-US/blog/damage-in-ue4
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Enemy components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UAttributeComponent* Attributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(EditAnywhere, Category = Pickup)
	int ChanceOfDroppingItem = 1; // Higher => Less likely

	UFUNCTION(BlueprintCallable)
	void UpdateWalkSpeed(float NewWalkSpeed) const;

	UFUNCTION(BlueprintCallable)
	void CancelWaypoints();

	UFUNCTION(BlueprintCallable)
	void SpawnRandomPickup();

	// Pickups spawn on death (ChanceOfDroppingItem dictates chance)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pickup)
	TSubclassOf<AItem> NormalAmmoPickup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pickup)
	TSubclassOf<AItem> FireAmmoPickup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pickup)
	TSubclassOf<AItem> HolyAmmoPickup;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pickup)
	TSubclassOf<AItem> HealthPickup;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Methods which will be called in ABP_Enemy in the event graph
	UFUNCTION(BlueprintCallable)	
	void DeathEnd();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	// Enemy logic methods
	void UpdateUI();
	void UpdateDeathLogic();
	void MoveToNextWaypoint();
	void Combat();
	void RemoveAIComponent() const;

	int32 CurrentWaypointIndex = 0;

	// Array of waypoints
	UPROPERTY(EditAnywhere, Category = "Waypoints")
	TArray<AActor*> Waypoints;

private:
	// Animation Montages
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* DeathMontage;

	// Pointer to player
	AHarker* Player;

	// Pointer to Survival Game Mode
	UPROPERTY()
	ASurvivalGameMode* SurvivalMode;
};
