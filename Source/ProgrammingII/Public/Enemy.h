// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class UAttributeComponent;
class UAnimMontage;
class UHealthBarComponent;
class ASurvivalGameMode;
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
	bool IsDead = false;

	UPROPERTY(EditAnywhere)
	float AttackDamage = 10.0f;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

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

	UFUNCTION(BlueprintCallable)	// This function will be called in ABP_Enemy
	void DeathEnd();				// in the event graph

	void UpdateUI();
	void UpdateDeathLogic();
	void MoveToNextWaypoint();
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

	// Pointer to Survival Game Mode
	UPROPERTY()
	ASurvivalGameMode* SurvivalMode;
};
