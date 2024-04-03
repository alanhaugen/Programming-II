// Fill out your copyright notice in the Description page of Project Settings.


#include "Umbrella.h"

AUmbrella::AUmbrella()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UmbrellaMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Umbrella Mesh"));

	UStaticMesh* StaticMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Mesh/Characters/Umbrella/SK_umbrella")));

	if (StaticMesh && UmbrellaMesh)
	{
		UmbrellaMesh->SetStaticMesh(StaticMesh);
	}
}
