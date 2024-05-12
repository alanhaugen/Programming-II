// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterState.h"
#include "Harker.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class UPointLightComponent;
class UBoxComponent;
class AItem;
class ACheckPoint;
class UAnimMontage;
class AInteractable;
class ABullet;

UENUM(BlueprintType)
enum class EAmmoTypes : uint8
{
	EAT_Normal,
	EAT_Fire,
	EAT_Holy
};

UCLASS()
class PROGRAMMINGII_API AHarker : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHarker();

	// Harker health
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	float Health = MaxHealth;

	// Amount of ammunition normal
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AmmunitionNormal = 10.0f;

	// Amount of ammunition incendiary
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AmmunitionFlame = 0.0f;

	// Amount of ammunition holy water
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AmmunitionHoly = 0.0f;
	
	// Variables for aiming with right mouse click
	UPROPERTY(BlueprintReadOnly)
	bool isZoomingIn = false;

	float ZoomFactor;

	// Variables for text when interacting with interactable objects
	UPROPERTY(BlueprintReadOnly, Category = Interactable)
	bool IsInteracting = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Interactable)
	AInteractable* CurrentInteractable;

	UPROPERTY(BlueprintReadOnly, Category = Interactable)
	bool bCanInteract = false; // Check if standing by next to interactable object

	// Public Equip Weapon function
	UFUNCTION(BlueprintCallable)
	void EquipWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Input
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* HarkerContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* AimAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ScopeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* InteractionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* CycleAmmunitionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* PauseAction;

	UFUNCTION(Blueprintcallable, Category = "Input")
	void Fire();

	UFUNCTION(Blueprintcallable, Category = "Input")
	void AimStart(const FInputActionValue& Value);

	UFUNCTION(Blueprintcallable, Category = "Input")
	void AimEnd(const FInputActionValue& Value);

	UFUNCTION(Blueprintcallable, Category = "Input")
	void Scope();

	UFUNCTION(Blueprintcallable, Category = "Input")
	void Interaction();

	UFUNCTION(Blueprintcallable, Category = "Input")
	void CycleAmmunition();

	UFUNCTION(Blueprintcallable, Category = "Input")
	void PauseGame();

	// Bullets spawn on Fire
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet")
	TSubclassOf<ABullet> BulletToSpawnNormal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet")
	TSubclassOf<ABullet> BulletToSpawnFire;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet")
	TSubclassOf<ABullet> BulletToSpawnHoly;

	// Check points
	UPROPERTY(VisibleInstanceOnly, Category = CheckPoint)
	ACheckPoint* CurrentCheckPoint;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = CheckPoint)
	TArray<ACheckPoint*> CheckPoints;

	UFUNCTION(BlueprintCallable)
	bool LoadCheckPoint();

	// You can expose some of your collision query data as properties to help customize and debug 
	// Here we expose the collision channel we want to run the query on, and set it to only hit Pawns.
	UPROPERTY(EditAnywhere, Category = "Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_Pawn;

	// Animation montages
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* DeathMontage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Attack logic for Harker's Fire function
	bool MeleeAttack();
	bool SpendAmmo();
	void SpawnBullet();
	bool CanFire() const;

	UFUNCTION(BlueprintCallable)	// This function will be called in ABP_Harker
	void MeleeAttackEnd();			// in the event graph

private:
	// Spring Arm
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	// Camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	// FPSCamera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCamera;

	// Default item lantern
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Lantern;
	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* LanternSpotLight;

	// Default item umbrella
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Umbrella;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBoxUmbrella;

	// Crossbow weapon
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Crossbow;

	// Umbrella for FPS mode
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* UmbrellaFPSMode;

	// Crossbow for FPS mode
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* CrossbowFPSMode;

	void Move(const FInputActionValue& Value);
	void LookAround(const FInputActionValue& Value);

	void UpdateItemVisibility();
	void SetItemVisibilityEquipped();
	void SetItemVisibilityUnequipped();
	void UpdateCameraBehaviour(bool isTurningWithCamera = false);

	// Equipment state of the player
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	// Action state of the player
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;
	
	// Player selected ammunition
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EAmmoTypes SelectedAmmo = EAmmoTypes::EAT_Normal;

	// Cooldown for firing crossbow
	bool IsFiring = false;

	// Set Delay time for firing
	void FireDelay();
	float FireDelayTime = 0.3f;

public:
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; };
};
