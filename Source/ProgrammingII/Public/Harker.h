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
class AItem;
class ACheckPoint;

UCLASS()
class PROGRAMMINGII_API AHarker : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHarker();

	// Harker health
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float Health = 100.0f;

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
	bool isZoomingIn = false;
	float ZoomFactor;

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
	class UInputMappingContext* FireIMC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* InteractionAction;

	UFUNCTION(Blueprintcallable, Category = "Input")
	void Fire();

	UFUNCTION(Blueprintcallable, Category = "Input")
	void AimStart(const FInputActionValue& Value);

	UFUNCTION(Blueprintcallable, Category = "Input")
	void AimEnd(const FInputActionValue& Value);

	UFUNCTION(Blueprintcallable, Category = "Input")
	void Interaction();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet")
	TSubclassOf<AActor> BulletToSpawn;

	// Check points
	UPROPERTY(VisibleInstanceOnly, Category = CheckPoint)
	ACheckPoint* CurrentCheckPoint;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = CheckPoint)
	TArray<ACheckPoint*> CheckPoints;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Spring Arm
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;

	// Camera
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	// Default items
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Lantern;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Umbrella;

	void Move(const FInputActionValue& Value);
	void LookAround(const FInputActionValue& Value);

	UPROPERTY(VisibleInstanceOnly, Category = Item)
	AItem* OverlappingItem;

	// State of the player
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

public:
	FORCEINLINE void SetOverlappingItem(AItem* item) { OverlappingItem = item; };
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; };
	FORCEINLINE AItem* GetOverlappingItem(AItem* item) const { return OverlappingItem; };
};
