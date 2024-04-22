// Fill out your copyright notice in the Description page of Project Settings.

#include "Item.h"
#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>
#include "Harker.h"
#include "SurvivalGameMode.h"

AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		Player = Cast<AHarker>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}

	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSpehereOverlap);
	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSpehereEndOverlap);
}

void AItem::OnSpehereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only pick up if player overlaps items
	if (Cast<AHarker>(OtherActor) == nullptr)
	{
		return;
	}

	switch (ItemType)
	{
	case EItemType::EIT_NormalArrow:
		Player->AmmunitionNormal += ItemAmount;
		break;

	case EItemType::EIT_FireArrow:
		Player->AmmunitionFlame += ItemAmount;
		break;

	case EItemType::EIT_HolyWaterArrow:
		Player->AmmunitionHoly += ItemAmount;
		break;

	case EItemType::EIT_Crossbow:
		Player->EquipWeapon();
		if (GetWorld())
		{
			ASurvivalGameMode* SurvivalMode = Cast<ASurvivalGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

			if (SurvivalMode)
			{
				SurvivalMode->CheckIfLastEnemy(); // Potentially start waves of enemies
			}
		}
		break;

	case EItemType::EIT_InstantDeath:
		Player->Health = 0;
		break;

	case EItemType::EIT_Health:
		Player->Health += ItemAmount;
		if (Player->Health > Player->MaxHealth)
		{
			Player->Health = Player->MaxHealth;
		}

		break;

	case EItemType::EIT_Special:
		if (GetWorld())
		{
			ASurvivalGameMode* SurvivalMode = Cast<ASurvivalGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

			if (SurvivalMode)
			{
				SurvivalMode->PickupSpecialItem(); // Potentially start waves of enemies
			}
		}

		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Item not supported."));
	}

	Destroy();
}

void AItem::OnSpehereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Movement rate in units cm/s
	RunningTime += DeltaTime;

	// MovmentRate * DeltaTime (cm/s) * (c/frame) = (cm/frame)
	AddActorWorldOffset(FVector(0.0f, 0.0f, Amplitude * FMath::Sin(RunningTime * TimeConstant)));
	SetActorRotation(GetActorRotation() + (FRotator(0.0f, 1.0f, 0.0f) * RotationSpeed * DeltaTime));
}

