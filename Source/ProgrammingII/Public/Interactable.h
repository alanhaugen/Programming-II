// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

class UBoxComponent;

UCLASS()
class PROGRAMMINGII_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractable();

	UFUNCTION()
	virtual void OnSpehereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSpehereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* Mesh;

	// Collision mesh for interactable
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Message)
	FText PreInteractionMessage = FText::FromString("Press E to Interact");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Message, meta = (MultiLine = true))
	FText InteractionMessage = FText::FromString("This is the text for the message box upon pressing E");
};
