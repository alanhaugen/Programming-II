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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BulletSettings")
	class UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSettings")
	FVector GuntipOffset;

	UPROPERTY(EditAnywhere, Category = "WeaponSettings")
	float MovementSpeed = 10.f;
};
