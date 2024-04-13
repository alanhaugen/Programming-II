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

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Message)
	FText PreInteractionMessage = FText::FromString("Press E to Interact");

	UPROPERTY(EditAnywhere, Category = Message)
	FText InteractionMessage = FText::FromString("This is the text for the message box upon pressing E");

protected:
	virtual void BeginPlay() override;

};
