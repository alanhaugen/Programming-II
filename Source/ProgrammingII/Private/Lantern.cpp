// Fill out your copyright notice in the Description page of Project Settings.


#include "Lantern.h"

ALantern::ALantern()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LanternMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lantern Mesh"));

	UStaticMesh* StaticMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, TEXT("/Game/Mesh/Characters/Lantern/SK_lantern")));

	if (StaticMesh && LanternMesh)
	{
		LanternMesh->SetStaticMesh(StaticMesh);
	}
}
