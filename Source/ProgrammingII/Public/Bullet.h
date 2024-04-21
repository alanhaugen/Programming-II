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

public:	

	AHarker* Character;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Bullet Settings")
	class UStaticMeshComponent* BulletMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet Type")
	EAmmoTypes BulletType = EAmmoTypes::EAT_Normal;

	UPROPERTY(EditAnywhere, Category = "Bullet Settings")
	float MovementSpeed = 10.f;
};
