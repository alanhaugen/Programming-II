// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "Internationalization/Text.h"
#include <Components/BoxComponent.h>

AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh for interactable object
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Umbrella"));
	Mesh->SetupAttachment(GetRootComponent());

	// Collision box which dictates when object becomes interactable to player
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionBox->SetupAttachment(Mesh);
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

