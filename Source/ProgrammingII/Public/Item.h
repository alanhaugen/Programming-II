#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UBoxComponent;
class AHarker;

UCLASS()
class PROGRAMMINGII_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();

	virtual void Tick(float DeltaTime) override;

	// Blueprint visible
	UPROPERTY(VisibleAnywhere, Category = "Item Parameters")
	float RunningTime;

	UPROPERTY(EditAnywhere, Category = "Item Parameters")
	float Amplitude = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Item Parameters")
	float TimeConstant = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Item Parameters")
	float RotationSpeed = 50.0f;

	UPROPERTY(EditAnywhere, Category = "Item Parameters")
	float ItemAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Item Parameters")
	int ItemType = 0;

protected:
	virtual void BeginPlay() override;

	// Collision mesh for item
	UBoxComponent* CollisionMesh;

	UFUNCTION()
	virtual void OnSpehereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSpehereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	AHarker* Player;

	enum EItemType
	{
		EIT_NormalArrow = 0,
		EIT_FireArrow,
		EIT_HolyWaterArrow,
		EIT_Crossbow = 5,
		EIT_InstantDeath,
		EIT_Health
	};
};
