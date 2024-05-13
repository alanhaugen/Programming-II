// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Harker.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class PROGRAMMINGII_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	AHarker* Character;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Blueprint editable bullet settings
	UPROPERTY(EditDefaultsOnly, Category = "Bullet Settings")
	class UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Settings")
	float BulletDamage = 25.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bullet Settings")
	EAmmoTypes BulletType = EAmmoTypes::EAT_Normal;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet Settings")
	float MovementSpeed = 10.0f;
};
