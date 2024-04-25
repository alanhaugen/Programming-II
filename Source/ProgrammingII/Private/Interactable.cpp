#include "Interactable.h"
#include <Components/BoxComponent.h>
#include "Harker.h"

AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh for interactable object
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	// Collision box which dictates when object becomes interactable to player
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionBox->SetupAttachment(Mesh);
}

void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::OnOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AInteractable::OnEndOverlap);
}

void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHarker* Player = Cast<AHarker>(OtherActor);

	if (Player)
	{
		Player->bCanInteract = true;
		Player->CurrentInteractable = this;
	}
}

void AInteractable::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHarker* Player = Cast<AHarker>(OtherActor);

	if (Player)
	{
		Player->bCanInteract = false;
	}
}
