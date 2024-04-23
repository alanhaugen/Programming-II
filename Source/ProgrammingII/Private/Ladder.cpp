// Fill out your copyright notice in the Description page of Project Settings.


#include "Ladder.h"
#include <Components/BoxComponent.h>

ALadder::ALadder()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionMeshTop = CreateDefaultSubobject<UBoxComponent>(FName("Top Collision Mesh"));
	CollisionMeshTop->SetupAttachment(Mesh);
}

void ALadder::BeginPlay()
{
	Super::BeginPlay();

	CollisionMeshTop->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnOverlap);
	CollisionMeshTop->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnEndOverlap);
}
