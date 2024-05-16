#include "Triggers/WaveTriggerer.h"
#include "GameModes/AdventureGameMode.h"
#include "Characters/Harker.h"
#include <Kismet/GameplayStatics.h>
#include <Components/BoxComponent.h>

AWaveTriggerer::AWaveTriggerer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the collision box for this game event trigger
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("Collision Box"));
	CollisionBox->SetupAttachment(GetRootComponent());
}

void AWaveTriggerer::BeginPlay()
{
	Super::BeginPlay();

	// Setup collision detection
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AWaveTriggerer::OnOverlap);
}

void AWaveTriggerer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWaveTriggerer::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Only trigger when Player enters the collision box
	if (Cast<AHarker>(OtherActor) == nullptr)
	{
		return;
	}

	// Trigger a wave
	if (GetWorld())
	{
		AAdventureGameMode* AdventureMode = Cast<AAdventureGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (AdventureMode)
		{
			// If this wave has already been triggered, don't do it again
			if (AdventureMode->CurrentWave == WaveToTrigger)
			{
				return;
			}

			// Potentially start waves of enemies
			AdventureMode->TriggerWave(WaveToTrigger);
		}
	}
}
